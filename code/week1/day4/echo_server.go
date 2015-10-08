package main

import (
	"fmt"
	"net"
)

func main() {
	ip := "127.0.0.1"
	port := 11211
	listen, err := net.ListenTCP("tcp", &net.TCPAddr{net.ParseIP(ip), port, ""})
	if err != nil {
		fmt.Println("Listen Error: ", err.Error())
		return
	}
	fmt.Println("Listening on ", ip, ":", port, ".")
	Server(listen)
}

func Server(listen *net.TCPListener) {
	for {
		conn, err := listen.AcceptTCP()
		if err != nil {
			fmt.Println("接受客户端连接异常:", err.Error())
			continue
		}
		fmt.Println("客户端连接来自:", conn.RemoteAddr().String())
		defer conn.Close()
		go func() {
			data := make([]byte, 128)
			for {
				i, err := conn.Read(data)
				fmt.Println("客户端发来数据:", string(data[0:i]))
				if err != nil {
					fmt.Println("读取客户端数据错误:", err.Error())
					break
				}
				conn.Write([]byte{'f', 'i', 'n', 'i', 's', 'h'})
			}

		}()
	}
}
