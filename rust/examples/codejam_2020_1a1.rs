use std::cell::RefCell;
use std::io::{stdin, BufRead, BufReader};
use std::str::{FromStr, SplitWhitespace};
type Result<T = (), E = Box<dyn std::error::Error>> = std::result::Result<T, E>;

fn get<T: FromStr>() -> Result<T, T::Err> {
    fn a(res: Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>> {
        res.ok().map(|s| Box::leak(s.into_boxed_str()).split_whitespace())
    }
    type It = std::cell::RefCell<std::iter::Flatten<std::iter::FilterMap<std::io::Lines<std::io::BufReader<std::io::Stdin>>,fn(Result<String,std::io::Error>)->Option<SplitWhitespace< 'static>>>>>;
    thread_local! {
        static IT: It = RefCell::new(BufReader::new(stdin()).lines().filter_map(a as fn(_) -> _).flatten());
    }
    IT.with(|it| it.borrow_mut().next().unwrap().parse())
}

fn main() -> Result {
    for i in 1..=get()? {
        print!("Case #{}: ", i);
        out((0..get::<usize>()?).map(|_| get()).collect::<Result<Vec<_>, _>>()?);
    }
    Ok(())
}

fn out(v: Vec<String>) {
    let mut begin = "";
    let mut end = "";
    let err = || println!("*");
    for s in &v {
        let mut split = s.split('*');
        if let Some(n) = split.next() {
            if n.len() > begin.len() {
                if n.starts_with(begin) {
                    begin = n;
                } else {
                    return err();
                }
            } else if !begin.starts_with(n) {
                return err();
            }
        }
        if let Some(n) = split.next_back() {
            if n.len() > end.len() {
                if n.ends_with(end) {
                    end = n;
                } else {
                    return err();
                }
            } else if !end.ends_with(n) {
                return err();
            }
        }
    }
    let mut s = begin.to_owned();
    v.iter().flat_map(|s| {
        let mut sp = s.split('*');
        sp.next(); sp.next_back();
        sp
    }).for_each(|subs| s.push_str(subs));

    s.push_str(end);
    println!("{}", s);
}