#/bin/bash




function install_centos()
{
	yum install gmock  gmock-devel
	yum install zlib   zlib-devel 
	yum install unzip
	yum install curl curl-devel
	yum install perl perl-IPC-Cmd
	yum install gtest gtest-devel


	echo "please install protobuf, version >= 3.5.15 , github: https://github.com/protocolbuffers/protobuf.git";

}


function install_ubuntu()
{
	wget https://github.com/AndyYoungDev/ubuntu-aliyun-sources/releases/download/shell/change.sh
	chmod a+x change.sh
	./change.sh
	
	sudo apt-get install libcurl4-openssl-dev 
	sudo apt-get install zlib-dev
	sudo apt-get install autoconf
	sudo apt-get install automake
	sudo apt-get install libtool
	sudo apt-get install bison flex


	echo "please install protobuf, version >= 3.5.15 , github: https://github.com/protocolbuffers/protobuf.git";

}

function check_system()
{

	echo "os:";
}




