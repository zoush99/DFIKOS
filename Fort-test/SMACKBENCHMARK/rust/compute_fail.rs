// @expect error

fn main() {
    let x = 10;
    let y = 20;
    let z = x + y;
    assert!(z != 30);
}
