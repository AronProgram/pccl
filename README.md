# 欢迎使用 PCCL 框架
PCCL框架，在腾讯开源TARS微服务框架的基础上，针对接入层处理HTTP协议，逻辑层处理PB等协议时，开发了一套后台开发脚手架的框架， 为后台开发工程师快速开发API节约大量时间，花很少的代价，打造属于自己高性能的Server.

##  PCCL框架特点
1. FastApi  接入层HTTP协议处理框架
    - 检查http协议头部
	- http协议路由处理
	- http协议过程处理
		- 路由初始化
		- 路由绑定
		- 路由函数处理
		- 鉴权处理
		- 错误处理
	- 处理结果返回 (结果主要是json)
		json 返回 （ 正常结果）
		302 返回 （重定向）
		403 返回（鉴权错误）
	- 支持jwt的鉴权处理
	
2. LogicSvr 逻辑层PB协议处理框架
	- 检查PB协议头部
	- PB协议路由处理
	- PB协议过程处理
		- 路由初始化
		- 路由绑定
		- 路由函数处理
		- 错误处理
	- 处理结果返回 (结果主要也PB)
		

3. 例子


## 代码结构
.
├── build      【编译目录】
├── cmake     
├── CMakeLists.txt
├── example    【例子】
├── LICENSE
├── README.md
├── src        【pccl 源码】
└── thirdparty 【第三方框架】

## 编译

  ****  注意，cmake版本3.7+的版本

1. https://github.com/AronProgram/pccl.git --recursive
2. cd build 
3. dos2unix compile.sh install-dep.sh
4. chmod +x compile.sh install-dep.sh
5. ./install-dep.sh
6. cat compile.sh > build.sh
7. ./build.sh 


## 安装
1. 

## 运行
1. 

## 日志
1. 

## 容器
1. 

## K8S
1. 

# 问题
1. 

## 参考资料
1. [Tars文档]: https://tarscloud.gitbook.io/

2. [jsoncpp文档]: http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html

3. [jsoncpp优化源码]: https://github.com/henshao/jsoncpp	"JsonCpp*的性能，使其更加适合运行在高并发的服务端。"

4. [cmake源码:]: https://github.com/Kitware/CMake.git

    


