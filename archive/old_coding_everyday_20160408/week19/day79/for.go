// Package main provides ...
package main

import (
	"fmt"
)

var str = "Hello,World!"

func normal_for() {
	len := len(str)
	for i := 0; i < len; i++ {
		ch := str[i]
		fmt.Println(i, ch)
	}
}

func range_for() {
	for i, ch := range "你好，世界！" {
		fmt.Println(i, ch)
	}
}

func main() {
	normal_for()
	fmt.Println("-------------------------------------------")
	range_for()
}
