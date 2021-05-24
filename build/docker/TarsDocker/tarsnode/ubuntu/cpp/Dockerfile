# Install ubuntu:v1.0 , from registry.cn-shanghai.aliyuncs.com/junyutong/ubuntu:v1.0
FROM ubuntu:latest

# workdir
WORKDIR /root/


# aliyun
RUN sed -i 's/http:\/\/archive.ubuntu.com/http:\/\/mirrors.aliyun.com/g'  /etc/apt/sources.list
RUN sed -i 's/http:\/\/security.ubuntu.com/http:\/\/mirrors.aliyun.com/g' /etc/apt/sources.list
RUN apt-get update


# install software
RUN apt-get install -y wget
RUN apt-get install -y curl
RUN apt-get install -y net-tools
RUN apt-get install -y dos2unix
RUN apt-get install -y iproute2


# copy source
COPY entrypoint.sh /sbin/
RUN dos2unix   /sbin/entrypoint.sh
RUN chmod 755  /sbin/entrypoint.sh
ENTRYPOINT     [ "/sbin/entrypoint.sh" ]

