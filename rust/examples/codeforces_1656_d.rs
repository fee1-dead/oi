use std::io::stdin;
use std::str::FromStr;
type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;
fn get<T: FromStr>() -> Result<T> where T::Err: std::error::Error + 'static {
    let mut s = String::new();
    stdin().read_line(&mut s)?;
    Ok(s.trim().parse()?)
}
fn main() -> Result<()> {
    for _ in 0..get()? {
        println!("{}", match get::<u64>()? {
            n if n % 2 == 1 => 2,
            n if n.count_ones() == 1 => -1,
            n => 2_i64.pow(n.trailing_zeros()+1),
        })
    }

    Ok(())
}