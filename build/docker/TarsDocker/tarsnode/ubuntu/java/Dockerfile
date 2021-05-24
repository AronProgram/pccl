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
RUN apt-get install -y iproute2
RUN apt-get install -y dos2unix

# copy source
RUN wget -P /opt/ https://repo.huaweicloud.com/java/jdk/8u202-b08/jdk-8u202-linux-x64.tar.gz
RUN tar -xzvf /opt/jdk-8u202-linux-x64.tar.gz  -C /opt/
RUN rm -f /opt/jdk-8u202-linux-x64.tar.gz 


# config java
ENV JAVA_HOME /opt/jdk1.8.0_202
ENV PATH      $PATH:$JAVA_HOME/bin


# entrypoint
COPY entrypoint.sh /sbin/
RUN dos2unix   /sbin/entrypoint.sh
RUN chmod 755  /sbin/entrypoint.sh
ENTRYPOINT     [ "/sbin/entrypoint.sh" ]
