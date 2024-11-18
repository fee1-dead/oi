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
    let n = get()?;
    let m = get::<i64>()?;
    let k = get::<i64>()?;
    let mut v = Vec::with_capacity(n);
    let mut sum = 0i64;
    for _ in 0..n {
        let a = get::<i64>()?;
        sum = sum.checked_add(a / m + 1).unwrap();
        v.push(a);
    }


    let mut lo = 1;
    let mut hi = sum + 1;
    while lo < hi {
        let mid = lo + (hi - lo) / 2;
        let base = mid * m;
        // how many targets does an arrow cover.
        // if it does 1 damage, it only covers 1.
        // if it does 2 damage, it covers 2.
        let impact = (base as f64).sqrt().ceil() as usize;
        let mut dd = vec![0i64; n];
        let mut d = vec![0i64; n];
        let mut prevdamage = 0;
        let mut quota = k;
        let mut fail = false;
        for (i, target) in v.iter().copied().enumerate() {
            if i != 0 {
                prevdamage += d[i - 1];
                d[i] += d[i - 1] + dd[i - 1];
                dd[i] += dd[i - 1];
            }
            let usage = if prevdamage >= target {
                0
            } else {
                (target - prevdamage) / base + 1
            };
            if usage > quota {
                fail = true;
                break;
            }
            quota -= usage;
            prevdamage += usage * base;
            if i < n {
                d[i] += -1 * usage;
                dd[i] += -2 * usage;
            }
            // i .. i + impact
            let lastimpacted = impact - 1 + i;
            if lastimpacted < n {
                dd[lastimpacted] += 2 * usage;
                // want to make pd zero at lastimpacted.
                let predict_pd = usage*base - usage*(impact as i64)*(impact as i64);
                d[lastimpacted] -= predict_pd;
                if lastimpacted + 1 < n {
                    let predict_d = -usage - usage*2* (impact as i64 - 1) - predict_pd;
                    d[lastimpacted + 1] -= predict_d;
                }
            }
        }
        if fail {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    println!("{lo}");

    Ok(())
}