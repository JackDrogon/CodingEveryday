// Package main provides ...
package main

import (
	"fmt"
)

func main() {
	slice_s := make([]int, 5, 10)

	fmt.Println("len: ", len(slice_s))
	fmt.Println("cap: ", cap(slice_s))
}
