#/bin/bash

METHOD=$1;
ARG1=$2;



DIR=`pwd`;


function update()
{
	git submodule update --init --recursive;
}

function build()
{
	cpuNumber=`grep -c 'processor' /proc/cpuinfo`;	
	echo "cpu number:$cpuNumber";
	
	cmake3 .. ;
	make -j $cpuNumber;
}


if [ "$METHOD" == "build" ]; then
	build;
	
elif [ "$METHOD" == "update" ]; then
	update;
	
else 
	build;
fi



