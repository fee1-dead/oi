use std::cell::RefCell;
use std::io::{stdin, BufRead, BufReader};
use std::str::{FromStr, SplitWhitespace};
type Result<T, E = Box<dyn std::error::Error>> = std::result::Result<T, E>;

fn get<T: FromStr>() -> Result<T, T::Err> {
    fn a(res: Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>> {
        res.ok()
            .map(|s| Box::leak(s.into_boxed_str()).split_whitespace())
    }
    type It = std::cell::RefCell<
        std::iter::Flatten<
            std::iter::FilterMap<
                std::io::Lines<std::io::BufReader<std::io::Stdin>>,
                fn(Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>>,
            >,
        >,
    >;
    thread_local! {
        static IT: It = RefCell::new(BufReader::new(stdin()).lines().filter_map(a as fn(_) -> _).flatten());
    }
    IT.with(|it| it.borrow_mut().next().unwrap().parse())
}
fn main() -> Result<()> {
    for i in 1..=get()? {
        print!("Case #{}: ", i);
        solve()?;
    }
    Ok(())
}

fn solve() -> Result<()> {
    let n: usize = get()?;
    let fun: Vec<u64> = (0..n).map(|_| get()).collect::<Result<_, _>>()?;
    let mut minimum = vec![0; n];
    // each node to list of nodes that point to them.
    // the index starts from 1, with 0 being the abyss
    // but the values are zero-indexed.
    let mut pointed_to_by: Vec<Vec<usize>> = vec![vec![]; n];
    let mut abyss_nodes: Vec<usize> = vec![];
    for i in 0..n {
        let pointed_to: usize = get()?;
        if pointed_to == 0 {
            abyss_nodes.push(i);
        } else {
            pointed_to_by[pointed_to - 1].push(i);
        }
    }
    fn dfs_min(node: usize, fun: &[u64], minimum: &mut [u64], pointed_to_by: &[Vec<usize>]) {
        let mut ret = std::u64::MAX;
        for &adj in &pointed_to_by[node] {
            dfs_min(adj, fun, minimum, pointed_to_by);
            ret = ret.min(minimum[adj]);
        }
        minimum[node] = if ret == std::u64::MAX {
            fun[node]
        } else {
            fun[node].max(ret)
        };
    }
    for &node in &abyss_nodes {
        dfs_min(node, &fun, &mut minimum, &pointed_to_by);
    }

    // to call this function the node's parent must be visited or an abyss.
    fn dfs_solve(
        node: usize,
        fun: &[u64],
        minimums: &mut [u64],
        pointed_to_by: &[Vec<usize>],
        total: &mut u64,
        add: bool,
    ) {
        // go through each child and find the minimum maximum node;
        let mut minimum = std::u64::MAX;
        let mut minimum_node = std::usize::MAX;
        for &adj in &pointed_to_by[node] {
            if minimums[adj] <= minimum {
                minimum = minimums[adj];
                minimum_node = adj;
            }
        }

        if add {
            if minimum_node == std::usize::MAX {
                *total += fun[node];
            } else {
                *total += minimum.max(fun[node]);
            }
        }

        if minimum_node != std::usize::MAX {
            dfs_solve(minimum_node, fun, minimums, pointed_to_by, total, false);
        }

        for &adj in &pointed_to_by[node] {
            if adj != minimum_node {
                dfs_solve(adj, fun, minimums, pointed_to_by, total, true);
            }
        }
    }

    let mut total = 0;
    for node in abyss_nodes {
        dfs_solve(node, &fun, &mut minimum, &pointed_to_by, &mut total, true);
    }
    println!("{}", total);

    Ok(())
}
