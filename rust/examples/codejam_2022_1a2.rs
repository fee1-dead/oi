// For any list of numbers we partition it into two sets by pushing to
// the smallest set first. Then we know that the difference is at most 10^9 because
// that is the maximum value of one integer. To minimize the difference between the two
// sets we come up with our input. The nearest smaller power of two to 10^9 is 2^29.
// Therefore we can minimize the difference between two sets to 2^29. By adding 2^28
// to the smallest set decreases the difference again, to 2^28. Therefore we can minimize
// the difference all the way to 2^0 = 1. However the problem dictates that the sum must be
// equal so the difference cannot be 1, so it will be 0.

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
    for _ in 1..=get()? {
        solve()?;
    }
    Ok(())
}

fn solve() -> Result<()> {
    assert!(get::<usize>()? == 100);
    let mut set1: Vec<usize> = Vec::new();
    let mut sum1 = 0;
    let mut sum2 = 0;

    let powers_of_2 = (0..=29).map(|x| 1usize << x);
    let onwards_128 = 129..129 + 70;
    for (i, n) in powers_of_2.clone().chain(onwards_128.clone()).enumerate() {
        if i != 0 {
            print!(" ")
        }
        print!("{}", n);
    }
    println!();

    let mut pick = |n: usize| {
        if sum1 < sum2 {
            set1.push(n);
            sum1 += n;
        } else {
            sum2 += n;
        }
    };

    onwards_128.for_each(&mut pick);

    for _ in 0..100 {
        pick(get()?);
    }

    powers_of_2.rev().for_each(&mut pick);

    for (i, n) in set1.into_iter().enumerate() {
        if i != 0 {
            print!(" ")
        }
        print!("{}", n);
    }
    println!();

    Ok(())
}
