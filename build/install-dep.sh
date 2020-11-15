#/bin/bash



### scl + gcc-9.1
yum install centos-release-scl
yum install devtoolset-9-gcc*
scl enable devtoolset-9 bash
scl --list


### 永久环境
echo "source /opt/rh/devtoolset-9/enable" >>/etc/profile


### tars 编译环境
yum install bison flex

### pccl 编译环境
yum install gmock  gmock-devel
yum install zlib   zlib-devel 
yum install unzip
yum install curl curl-devel
yum install perl perl-IPC-Cmd
yum install gtest gtest-devel

### 子模块
git submodule update --init --recursive

git clone https://github.com/protocolbuffers/protobuf.git thirdpaty/protobuf --recursive
git clone https://github.com/TarsCloud/TarsProtocol.git   thirdpaty/TarsCpp/servant/protocol
git clone https://github.com/TarsCloud/tars-unittest.git  thirdpaty/TarsCpp/unittest




