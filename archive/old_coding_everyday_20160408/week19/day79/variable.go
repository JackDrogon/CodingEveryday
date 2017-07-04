// Package main provides ...
package main

import "fmt"

var x = 10

func variable() {
	ix := 10
	sy := "Hello"
	fmt.Println(ix, sy)
}

// or func add(x int, y int) int {
func add(x, y int) int {
	return x + y
}

func main() {
	fmt.Println("X: ", x)
	fmt.Println(add(11, 12))
	variable()
}
