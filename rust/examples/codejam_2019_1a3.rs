use std::cell::RefCell;
use std::collections::HashSet;
use std::io::{stdin, BufRead, BufReader};
use std::str::{FromStr, SplitWhitespace};
type Result<T = (), E = Box<dyn std::error::Error>> = std::result::Result<T, E>;

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

fn main() -> Result {
    for i in 1..=get()? {
        print!("Case #{}: ", i);
        out((0..get::<usize>()?)
            .map(|_| get())
            .collect::<Result<Vec<_>, _>>()?);
    }
    Ok(())
}

fn out(mut s: Vec<String>) {
    let prevlen = s.len();
    s.iter_mut().for_each(|s| *s = s.chars().rev().collect());
    s.sort_unstable();

    let mut prefixes_used = HashSet::new();

    while !s.is_empty() {
        let mut max_prefix = (String::new(), std::usize::MAX);
        for (idx, w) in s.windows(2).enumerate() {
            let a = &w[0];
            let b = &w[1];
            let mut s: String = a
                .chars()
                .zip(b.chars())
                .take_while(|(a, b)| a == b)
                .map(|(a, _)| a)
                .collect();
            while prefixes_used.contains(&s) {
                s.pop();
            }

            if s.len() > max_prefix.0.len() {
                max_prefix = (s, idx)
            }
        }

        if max_prefix.1 == std::usize::MAX {
            break;
        }

        prefixes_used.insert(max_prefix.0);

        s.remove(max_prefix.1);
        s.remove(max_prefix.1);
    }

    println!("{}", prevlen - s.len());
}
