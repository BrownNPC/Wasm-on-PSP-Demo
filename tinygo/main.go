package main

import "time"

import rl "github.com/gen2brain/raylib-go/raylib"

func main() {

	// debugPrint("hello wasm!!")
	rl.InitWindow(480, 272, "Psp test")
	for {
		time.Sleep(time.Millisecond * 16)
	}
}
