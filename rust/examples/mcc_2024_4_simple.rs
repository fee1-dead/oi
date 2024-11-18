use std::fs::File;

type Result<T, E = Box<dyn std::error::Error>> = std::result::Result<T, E>;

pub fn get<T: std::str::FromStr>() -> Result<T, T::Err> {
    use std::io::BufRead;
    use std::str::SplitWhitespace;

    fn a(res: Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>> {
        res.ok()
            .map(|s| Box::leak(s.into_boxed_str()).split_whitespace())
    }
    type It = std::cell::RefCell<
        std::iter::Flatten<
            std::iter::FilterMap<
                std::io::Lines<std::io::BufReader<std::fs::File>>,
                fn(Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>>,
            >,
        >,
    >;
    thread_local! {
        static IT: It = std::cell::RefCell::new(std::io::BufReader::new(File::open("in").unwrap()).lines().filter_map(a as fn(_) -> _).flatten());
    }
    IT.with(|it| it.borrow_mut().next().unwrap().parse())
}

fn main() -> Result<()> {
    let n = get::<usize>()?;
    let mut v = Vec::with_capacity(n);
    for _ in 0..n {
        let a = get::<i64>()?;
        let b = get::<i64>()?;
        v.push((a, -b));
    }
    // if there is one pair, we're forcing a. if there are two pairs, we're forcing b.
    let mut forcing_a = (n % 2) == 1;
    // everyone wants to force the worse outcome for the other person
    // highest a - b goes first
    v.sort_unstable_by_key(|(a, b)| a - b);
    let mut sum = 0;

    for (adiff, bdiff) in v {
        if forcing_a {
            sum += adiff;
        } else {
            sum += bdiff;
        }
        forcing_a = !forcing_a;
    }
    println!("{sum}");
    Ok(())
}