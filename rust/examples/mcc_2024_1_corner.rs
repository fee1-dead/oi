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
                std::io::Lines<std::io::BufReader<std::io::Stdin>>,
                fn(Result<String, std::io::Error>) -> Option<SplitWhitespace<'static>>,
            >,
        >,
    >;
    thread_local! {
        static IT: It = std::cell::RefCell::new(std::io::BufReader::new(std::io::stdin()).lines().filter_map(a as fn(_) -> _).flatten());
    }
    IT.with(|it| it.borrow_mut().next().unwrap().parse())
}

fn main() -> Result<()> {
    for _ in 0..get::<u32>()? {
        let n: u64 = get()?;
        let m: u64 = get()?;
        let a: u64 = get()?;
        let b: u64 = get()?;

        let flag = a <= n && b <= m && (a == n || b == m);
        let flag2 = b <= n && a <= m && (b == n || a == m);

        println!("{}", if flag || flag2 { "YES" } else { "NO" })
    }
    Ok(())
}