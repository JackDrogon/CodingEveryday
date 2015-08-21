package main

import (
	"fmt"
	"math/rand"
)

func add(x int, y int) int {
	return x + y
}

func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func main() {
	fmt.Println("Hello, World!")
	fmt.Println("My favourite number is", rand.Intn(10))
	fmt.Println(add(42, 43))
}
