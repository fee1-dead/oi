use std::cell::RefCell;
use std::collections::HashSet;
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
    for _ in 1..=get()? {
        solve()?;
    }
    Ok(())
}

fn solve() -> Result<()> {
    let n: usize = get()?;
    let k: usize = get()?;
    let mut visited: HashSet<usize> = HashSet::with_capacity(n);
    let mut num = get()?;
    visited.insert(num);
    let mut passages: usize = get()?;
    let mut rolled = false;
    for _ in 0..(k / 2) {
        while visited.contains(&num) {
            num += 1;
        }
        visited.insert(num);
        if num > n {
            if rolled {
                break;
            } else {
                num = 1;
                rolled = true;
                continue;
            }
        }
        println!("T {}", num);
        let _: usize = get()?;
        passages += get::<usize>()?;
        println!("W");
        let visi = get()?;
        let psgs: usize = get()?;
        if visited.contains(&visi) {
            passages -= 1;
        } else {
            passages += psgs - 1;
        }
    }
    let pas_f = passages as f64;
    let ans = pas_f / 2.0 * n as f64 / k as f64;
    println!("E {}", ans as usize);
    Ok(())
}
