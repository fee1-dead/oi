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
    for _ in 0..get::<usize>()? {
        let n = get::<usize>()?;
        let mut v = Vec::with_capacity(n);
        for _ in 0..n {
            v.push(get::<u64>()?);
        }
        v.sort_unstable();
        let mut x = v.pop().unwrap() % 1000000007;

        for y in v.into_iter().rev() {
            x = ((2*x) % 1000000007 + y % 1000000007) % 1000000007;
        }
        println!("{x}");
    }
    Ok(())
}