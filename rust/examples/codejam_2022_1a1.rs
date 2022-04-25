use std::cell::RefCell;
use std::io::{stdin, BufRead, BufReader};
use std::iter::repeat;
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
        static IT: It  = RefCell::new(BufReader::new(stdin()).lines().filter_map(a as fn(_) -> _).flatten());
    }
    IT.with(|it| it.borrow_mut().next().unwrap().parse())
}
fn main() -> Result<()> {
    for i in 1..=get()? {
        print!("Case #{}: ", i);
        out(get()?);
    }
    Ok(())
}

fn out(mut s: String) {
    let mut i = 0;
    while i < s.len() {
        let news = s
            .chars()
            .enumerate()
            .flat_map(|(idx, c)| repeat(c).take(if idx == i { 2 } else { 1 }));
        if news.clone().lt(s.chars()) {
            s = news.collect();
            i += 1;
        }
        i += 1;
    }
    println!("{}", s);
}
