package main

//井字棋服务端
import (
	"encoding/json"
	"fmt"
	"net"
	"strconv"
	"strings"
)

type game_pos struct {
	PosX   uint
	PosY   uint
	client uint8
}
type Data struct {
	Client string `json:"client"`
	Pos    string `json:"pos"`
}

var ClientList [2]net.Conn

func handle_pos(coordStr string) {
	// 使用逗号分割字符串
	parts := strings.Split(coordStr, ",")

	// 确保分割得到两个部分
	if len(parts) == 2 {
		// 解析每个坐标值
		x, err1 := strconv.Atoi(parts[0])
		y, err2 := strconv.Atoi(parts[1])

		// 检查是否有错误发生
		if err1 == nil && err2 == nil {
			fmt.Println("坐标值：", x, y)
		} else {
			fmt.Println("解析坐标值时发生错误")
		}
	} else {
		fmt.Println("无效的坐标字符串")
	}
}

func handle_rev_msg(rev_msg string) {
	var d Data
	rev_msg = strings.ReplaceAll(rev_msg, "\x00", "")
	err := json.Unmarshal([]byte(rev_msg), &d)
	if err != nil {
		fmt.Println("解析JSON失败:", err)
		return
	}
	// 输出解析后的结果
	fmt.Println("Client:", d.Client)
	fmt.Println("Pos:", d.Pos)
	handle_pos(d.Pos)
}

func handleConnect(conn net.Conn) {
	defer conn.Close()
	for {
		buffer := make([]byte, 1024)
		_, err := conn.Read(buffer)
		if err != nil {
			fmt.Println("Read error")
			return
		}
		client := conn.RemoteAddr()
		fmt.Println("client", client)
		fmt.Println("Receive data", string(buffer))
		for i := 0; i < 2; i++ {
			if ClientList[i] != nil {
				ClientList[i].Write([]byte(string(buffer)))
			}
		}
		conn.Write([]byte("win"))
		str := string(buffer)
		handle_rev_msg(str)
	}
}

func main() {
	listener, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		return
	}
	str := `{"client":"a","pos":"1,2"}`
	handle_rev_msg(str)
	defer listener.Close()
	fmt.Println("Server listening on localhost:8080")
	i := 0
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err.Error())
			return
		}
		ClientList[i] = conn
		i++
		go handleConnect(conn)
	}
}
