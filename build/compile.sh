#/bin/bash

CMD1=$1;
CMD2=$2;



DIR=`pwd`;

function build()
{
	cpuNumber=`grep -c 'processor' /proc/cpuinfo`;
	
	cmake3 .. ;
	make -j $cpuNumber;
}



