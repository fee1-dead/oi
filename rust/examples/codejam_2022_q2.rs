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
        print!("Case #{}: ", i);
        out(&(0..12).map(|_| get()).collect::<Result<Vec<_>, _>>()?);
    }
    Ok(())
}

fn out(printers: &[u32]) {
    let mins = (0..4).map(|i| printers.iter().skip(i).step_by(4).min().unwrap());
    let mut remaining = 1000000u32;
    let mut numbers = [0; 4];
    for (&m, n) in mins.zip(&mut numbers) {
        let val = m.min(remaining);
        *n = val;
        remaining -= val;
    }
    if remaining != 0 {
        println!("IMPOSSIBLE");
    } else {
        for (num, i) in numbers.into_iter().enumerate() {
            if num != 0 { print!(" ") }
            print!("{}", i);
        }
        println!()
    }
}