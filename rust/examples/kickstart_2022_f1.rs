// begin helper
mod helper {
    use std::convert::TryInto;
    use std::cell::RefCell;
    use std::collections::{HashMap, HashSet};
    use std::hash::{BuildHasherDefault, Hasher};
    use std::io::{stdin, BufRead, BufReader};
    use std::mem::size_of;
    use std::ops::BitXor;
    use std::str::{FromStr, SplitWhitespace};

    pub type Result<T = (), E = Box<dyn std::error::Error>> = std::result::Result<T, E>;
    pub type FxHashMap<K, V> = HashMap<K, V, BuildHasherDefault<FxHasher>>;
    pub type FxHashSet<V> = HashSet<V, BuildHasherDefault<FxHasher>>;
    #[derive(Default)]
    pub struct FxHasher {
        hash: usize,
    }
    
    #[cfg(target_pointer_width = "32")]
    const K: usize = 0x9e3779b9;
    #[cfg(target_pointer_width = "64")]
    const K: usize = 0x517cc1b727220a95;
    
    impl FxHasher {
        #[inline]
        fn add_to_hash(&mut self, i: usize) {
            self.hash = self.hash.rotate_left(5).bitxor(i).wrapping_mul(K);
        }
    }
    
    impl Hasher for FxHasher {
        #[inline]
        #[allow(clippy::len_zero)]
        fn write(&mut self, mut bytes: &[u8]) {
            #[cfg(target_pointer_width = "32")]
            let read_usize = |bytes: &[u8]| u32::from_ne_bytes(bytes[..4].try_into().unwrap());
            #[cfg(target_pointer_width = "64")]
            let read_usize = |bytes: &[u8]| u64::from_ne_bytes(bytes[..8].try_into().unwrap());
            
            let mut hash = FxHasher { hash: self.hash };
            assert!(size_of::<usize>() <= 8);
            while bytes.len() >= size_of::<usize>() {
                hash.add_to_hash(read_usize(bytes) as usize);
                bytes = &bytes[size_of::<usize>()..];
            }
            if (size_of::<usize>() > 4) && (bytes.len() >= 4) {
                hash.add_to_hash(u32::from_ne_bytes(bytes[..4].try_into().unwrap()) as usize);
                bytes = &bytes[4..];
            }
            if (size_of::<usize>() > 2) && bytes.len() >= 2 {
                hash.add_to_hash(u16::from_ne_bytes(bytes[..2].try_into().unwrap()) as usize);
                bytes = &bytes[2..];
            }
            
            if (size_of::<usize>() > 1) && bytes.len() >= 1 {
                hash.add_to_hash(bytes[0] as usize);
            }
            self.hash = hash.hash;
        }
    
        #[inline]
        fn write_u8(&mut self, i: u8) {
            self.add_to_hash(i as usize);
        }
    
        #[inline]
        fn write_u16(&mut self, i: u16) {
            self.add_to_hash(i as usize);
        }
    
        #[inline]
        fn write_u32(&mut self, i: u32) {
            self.add_to_hash(i as usize);
        }
    
        #[cfg(target_pointer_width = "32")]
        #[inline]
        fn write_u64(&mut self, i: u64) {
            self.add_to_hash(i as usize);
            self.add_to_hash((i >> 32) as usize);
        }
    
        #[cfg(target_pointer_width = "64")]#[inline]fn write_u64(&mut self, i: u64) {self.add_to_hash(i as usize);}
        #[inline]fn write_usize(&mut self, i: usize) {self.add_to_hash(i);}
        #[inline]fn finish(&self) -> u64 {self.hash as u64}}

    #[macro_export]
    macro_rules! memoize {
        {fn $name:ident[$CACHE:ident]( $( $arg:ident : $ty:ty ),+ $(, $( @($($env_arg:ident: $env_arg_ty:ty),+$(,)?) )? )? ) -> $RetTy: ty $bl:block} => {
            thread_local! {
                static $CACHE: std::cell::RefCell<FxHashMap<($($ty,)+), $RetTy>> = std::cell::RefCell::default();
            }
            
            fn $name  ( $( $arg : $ty, )+ $($($($env_arg: $env_arg_ty,)+)?)? ) -> $RetTy {                
                fn inner( $( $arg : $ty, )+ $( $( $( $env_arg: $env_arg_ty,  )+ )? )? ) -> $RetTy $bl

                let args = ( $($arg,)+ );

                $CACHE.with(|__c| {
                    if let Some(res) = __c.borrow().get(&args) {
                        return res.clone()
                    }

                    let newargs = args.clone();
                    let ($($arg,)+) = args;
                    let result = inner( $($arg,)+ $($( $( $env_arg, )+ )?)? );
                    __c.borrow_mut().insert(newargs, result.clone());
                    result
                })
            }
        };
    }

    pub fn get<T: FromStr>() -> Result<T, T::Err> {
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
            static IT: It = RefCell::new(BufReader::new(stdin()).lines().filter_map(a as fn(_) -> _).flatten());
        }
        IT.with(|it| it.borrow_mut().next().unwrap().parse())
    }
}
pub use helper::*; // pub to prevent unused warnings
// end helper

#[derive(PartialEq, Eq, PartialOrd, Ord)]
pub struct Fabric(String, i32, i32, usize);

fn main() -> Result<()> {
    for i in 1..=get()? {
        let cap = get()?;
        let mut v = Vec::with_capacity(cap);
        for _ in 0..cap {
            v.push(Fabric(get()?, get()?, get()?, 0));
        }
        v.sort_unstable_by_key(|f| (f.0.clone(), f.2));
        for (i, f) in v.iter_mut().enumerate() {
            f.3 = i;
        }
        v.sort_unstable_by_key(|f| (f.1, f.2));
        println!("Case #{}: {}", i, v.iter_mut().enumerate().filter(|(n, x)| x.3 == *n).count());
    }
    Ok(())
}