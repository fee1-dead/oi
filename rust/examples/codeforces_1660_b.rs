use std::io::{stdin, BufRead};
use std::str::FromStr;
type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;
fn get<T: FromStr>(mut it: impl Iterator<Item = &'static str>) -> Result<T>
where
    T::Err: std::error::Error + 'static,
{
    Ok(it.next().unwrap().trim().parse()?)
}
fn main() -> Result<()> {
    let rdr = stdin();
    let lock = rdr.lock();
    let lines = lock.lines();
    let mut it = lines
        .filter_map(|s| {
            s.ok()
                .map(|s| Box::leak(s.into_boxed_str()).split_whitespace())
        })
        .flatten();
    for _ in 0..get(&mut it)? {
        let mut arr: Vec<u64> = (0u32..get(&mut it)?)
            .map(|_| get(&mut it).unwrap())
            .collect();
        arr.sort_unstable();
        println!(
            "{}",
            ["NO", "YES"][match &arr[..] {
                [] | [0] => unreachable!(),
                [1] => true,
                [2..=u64::MAX] => false,
                [.., a, b] => b - a <= 1,
            } as usize]
        )
    }
    Ok(())
}
