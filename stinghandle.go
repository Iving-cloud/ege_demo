package main

import (
	"fmt"
)

func ConvertbyCaptial(str string) string {
	var words [100]byte
	runes := []byte(str)
	p := 0
	for i := 0; i < len(runes); i++ {
		if i!=0 && runes[i] >= 'A' && runes[i] <= 'Z' {
			words[p] = '_'
			p++
			words[p] = runes[i]
			p++
		}else if i == 0 {
			words[p] = runes[i]
			p++
		} else{
			runes[i]-=('a'-'A')
			words[p]=(runes[i])
			p++
		}
	}
	fmt.Println(string(words[0:p]))
	return string(words[0:p])
}

func main() {
	var str string
	fmt.Scanln(&str)
	ConvertbyCaptial(str)
}