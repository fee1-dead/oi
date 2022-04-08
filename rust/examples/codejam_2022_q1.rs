use std::cell::RefCell;
use std::io::{stdin, BufRead, BufReader};
use std::str::{FromStr, SplitWhitespace};
type Result<T, E = Box<dyn std::error::Error>> = std::result::Result<T, E>;

fn get<T: FromStr>() -> Result<T, T::Err> {
    fn a(res: Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>> {
        res.ok().map(|s| Box::leak(s.into_boxed_str()).split_whitespace())
    }
    thread_local! {
        static IT: std::cell::RefCell<std::iter::Flatten<std::iter::FilterMap<std::io::Lines<std::io::BufReader<std::io::Stdin>>,fn(Result<String,std::io::Error>)->Option<SplitWhitespace< 'static>>>>>  = RefCell::new(BufReader::new(stdin()).lines().filter_map(a as fn(_) -> _).flatten());
    }
    IT.with(|it| it.borrow_mut().next().unwrap().parse())
}
fn main() -> Result<()> {
    for i in 1..=get()? {
        println!("Case #{}:", i);
        out(get()?, get()?);
    }
    Ok(())
}

fn out(rows: u8, columns: u8) {
    for row in 0..rows {
        for column in 0..columns {
            if let (0, 0) = (row, column) {
                print!("..");
            } else {
                print!("+-");
            }
        }
        println!("+");
        for column in 0..columns {
            if let (0, 0) = (row, column) {
                print!("..");
            } else {
                print!("|.");
            }
        }
        println!("|");
    }
    for _ in 0..columns {
        print!("+-");
    }
    println!("+");
}