FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get install -y postgresql libpq-dev python3 python3-pip g++ clang libc++-dev libc++abi-dev
RUN apt-get clean

RUN pip3 install --upgrade pip
RUN pip3 install termcolor toml psycopg2 markdown
