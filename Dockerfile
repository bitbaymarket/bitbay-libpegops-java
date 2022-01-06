FROM ubuntu:xenial AS builder

RUN echo mark1
RUN apt-get update
RUN apt-get install -y tree
RUN apt-get install -y make
RUN apt-get install -y gcc g++
RUN apt-get install -y curl
RUN apt-get install -y bzip2
RUN apt-get install -y automake
RUN apt-get install -y autoconf
RUN apt-get install -y libtool
RUN apt-get install -y pkg-config
RUN apt-get install -y default-jdk-headless
RUN apt-get install -y libboost-dev libboost-system1.58-dev
RUN apt-get install -y libssl-dev

RUN mkdir -p /src
RUN mkdir -p /src/obj
COPY bay /src/bay
COPY Makefile /src
RUN tree /src
WORKDIR /src
ENV JAVA_HOME /usr/lib/jvm/java-8-openjdk-amd64
RUN make
RUN make test