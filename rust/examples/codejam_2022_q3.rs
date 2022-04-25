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
        out((0..get::<u32>()?)
            .map(|_| get())
            .collect::<Result<Vec<_>, _>>()?);
    }
    Ok(())
}

fn out(mut numbers: Vec<u32>) {
    numbers.sort_unstable();
    let ans = numbers
        .into_iter()
        .fold(1u32, |run, new| if run <= new { run + 1 } else { run })
        - 1;

    println!("{}", ans);
}
