extern crate semver;
use semver::Version;
use std::thread::Thread;
use std::sync::{Arc, Mutex};

fn main() {
    println!("Hello,World!");



    assert!(Version::parse("1.2.3") == Ok(Version {
        major: 1u64,
        minor: 2u64,
        patch: 3u64,
        pre: vec!(),
        build: vec!(),
    }));

    println!("Version compared successfully!");



    let mut v = vec![];
    v.push("Hello");
    // let x = &v[0];
    let x = &v[0].clone();
    v.push("world");
    println!("{}", x);


    for _ in range(0u, 10u) {
        Thread::spawn(move || {
            println!("Hello,World!");
        });
    }



    // let mut numbers = vec![1i, 2i, 3i];
    let numbers = Arc::new(Mutex::new(vec![1i, 2i, 3i]));
    for i in range(0u, 3u) {
        let number = numbers.clone();
        Thread::spawn(move || {
            let mut array = number.lock().unwrap();
            (*array)[i] += 1;
            // for j in range(0, 3) { numbers[j] += 1; }
            println!("numbers[{}] is {}", i, (*array)[i]);
        });
    }



    let vec = vec![1i, 2, 3];
    for i in range(0u, 3) {
        Thread::spawn(move || {
            println!("{}", vec[i]);
        }).detach();
    }
}
