// Package main
package main

import (
	"fmt"
)

func main() {
	type data struct{ a int }
	var d = data{1234}
	var p *data
	p = &d
	fmt.Printf("%p, %v\n", p, p.a) // 直接⽤用指针访问⺫⽬目标对象成员，⽆无须转换。
}
