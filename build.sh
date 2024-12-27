


rm src/app.*
# rm tinygo/app.wasm

set -e
# compile go code to wasm
cd ./tinygo && tinygo build -o app.wasm -target target.json -no-debug main.go

cd ..

echo  transpile wasm to C
w2c2 -p ./tinygo/app.wasm ./src/app.c
