use std::fs::File;
use std::io::{BufRead, BufReader};

type Result<T, E = Box<dyn std::error::Error>> = std::result::Result<T, E>;

fn main() -> Result<()> {
    let mut l = BufReader::new(File::open("in")?).lines();
    let l1 = l.next().unwrap()?;
    let (n, m) = l1.split_once(' ').unwrap();
    let n = n.parse()?;
    let m = m.parse()?;
    let mut people: Vec<(u64, usize, bool)> = Vec::with_capacity(n);
    let l2 = l.next().unwrap()?;
    for (idx, a) in l2.split_whitespace().enumerate() {
        people.push((a.parse()?, idx, false));
    }
    assert_eq!(n, people.len());
    people.sort_unstable();
    people.iter_mut().take(m).for_each(|x| x.2 = true);

    people.sort_unstable_by_key(|x| x.1);

    for (_, i, b) in people {
        if i != 0 {
            print!(" ");
        }
        print!("{}", b as u8);
    }
    println!();

    Ok(())
}