// Package main provides ...
package main

import (
	"fmt"
	"io"
	"os"
)

func CopyFile(dstName, srcName string) (written int64, err error) {
	src, err := os.Open(srcName)
	if err != nil {
		return
	}
	defer src.Close()

	dst, err := os.Create(dstName)
	if err != nil {
		return
	}
	defer dst.Close()

	return io.Copy(dst, src)
}

func main() {
	fmt.Println("Counting...")
	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}
	fmt.Println("Done...")
}
