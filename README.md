# grpc_server

### Following steps in this link [install gRPC](https://grpc.io/docs/languages/cpp/quickstart/) or ```enter``` cmd below.
1. ```export MY_INSTALL_DIR=$HOME/.localexport MY_INSTALL_DIR=$HOME/.local```
2. ```mkdir -p $MY_INSTALL_DIR```
3. ```export PATH="$MY_INSTALL_DIR/bin:$PATH"```
4. ```sudo apt install -y cmake```
5. ```sudo apt install -y build-essential autoconf libtool pkg-config```
6. ```git clone --recurse-submodules -b v1.71.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc```
7. Build and install gRPC and Protocol Buffer
```
cd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_CXX_STANDARD=17 \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
make -j 4
make install
popd
```
### Clone example and build.
```
1. git clone https://github.com/Nam97UTC/grpc_server.git
2. mkdir build && cd build
3. cmake ..
4. make
5. Run executed file and enjoy
```
### setup gRPC
1. Change configuration address in app.json file
