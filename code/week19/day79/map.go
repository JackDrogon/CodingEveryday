// Package main provides ...
package main

import "fmt"

type PersonInfo struct {
	id      string
	name    string
	address string
}

var persons map[string]PersonInfo

func main() {
	persons := make(map[string]PersonInfo)

	persons["1234"] = PersonInfo{"1234", "Tom", "Room 123..."}
	persons["1"] = PersonInfo{"1", "Jack", "Room 1..."}

	person, ok := persons["1234"]

	if ok {
		fmt.Println("Found person:", person.id, person.name, person.address)
	} else {
		fmt.Println("Not found person")
	}
}
