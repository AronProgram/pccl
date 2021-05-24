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

	apt-get install gcc
	apt-get install build-essential
	apt-get install libcurl4-openssl-dev 
	apt-get install zlib1g zlib1g-dev
	apt-get install autoconf
	apt-get install automake
	apt-get install libtool
	apt-get install bison flex
	apt-get install libprotobuf-dev protobuf-compiler


}

function check_system()
{

	echo "os:";
}




