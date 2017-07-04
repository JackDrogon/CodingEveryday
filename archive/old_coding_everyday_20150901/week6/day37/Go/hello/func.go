// Package main provides ...
package main

import (
	"fmt"
	"math"
)

func adder(sum int) func(int) int {
	return func(x int) int {
		sum += x
		return x
	}
}

func main() {
	hypot := func(x, y float64) float64 {
		return math.Sqrt(x*x + y*y)
	}
	fmt.Println(hypot(3, 4))
}
