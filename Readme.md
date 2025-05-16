# Golang or (any other wasi-supported lang) on PSP 


first we compile the code to wasi (wasm), then compile the wasm to C.



make sure pspdev is installed and added to your path.
then install raylib4psp
```
  git clone https://github.com/BrownNPC/raylib -b raylib4Consoles
  cd raylib/src
  make PLATFORM=PLATFORM_PSP
  make PLATFORM=PLATFORM_PSP install
```



install tinygo

https://github.com/tinygo-org/tinygo/releases


as of now, the latest is 0.35
```
# replace this link with the one appropriate for your system
wget https://github.com/tinygo-org/tinygo/releases/download/v0.35.0/tinygo0.35.0.linux-amd64.tar.gz 
mkdir tinygo_extract && cd tinygo_extract
tar -xf ../tinygo0.35.0.linux-amd64.tar.gz 
cd tinygo
cp -r * ~/.local/


tinygo version
# make sure you have the golang version tinygo requires
```



also install [W2C2](https://github.com/turbolent/w2c2)
feel free to paste these commands
```
git clone https://github.com/turbolent/w2c2
cd w2c2

# Compile it: (make sure you have a C compiler, CMake and Make installed)

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# create an install directory for w2c2
mkdir ~/w2c2
export W2C2_DIR=~/w2c2
export PATH="$W2C2_DIR/bin":$PATH
# also add this to your .bashrc or .zshrc

install -d "$W2C2_DIR"/{bin,lib,include/{w2c2,wasi}}

install -s w2c2/w2c2 "$W2C2_DIR"/bin/

# optionally install the libs to your path 
# install wasi/libw2c2wasi.a "$W2C2_DIR"/lib/
# install -m 0644 ../w2c2/w2c2_base.h "$W2C2_DIR"/include/w2c2/
# install -m 0644 ../wasi/wasi.h "$W2C2_DIR"/include/wasi/

echo please add these lines to ~/.bashrc or ~/.zshrc
echo export W2C2_DIR=~/w2c2
echo export PATH="$W2C2_DIR/bin":$PATH
```


Now that the project is setup, 
```
  mkdir build
  ./build.sh
  cd build/
  psp-cmake ..
  make
```

![image](https://github.com/user-attachments/assets/d111fd96-a954-4237-b0cc-455ac7058686)


props to these articles
https://00f.net/2023/12/11/webassembly-compilation-to-c/
https://github.com/aethiopicuschan/wasm3-tinygo-psp/
