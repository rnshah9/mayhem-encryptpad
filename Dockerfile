# Build Stage
FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y qtbase5-dev gcc g++ make pkg-config zlib1g-dev libbotan-2-dev libbz2-dev python

ADD . /mayhem-encryptpad
WORKDIR /mayhem-encryptpad

RUN ./configure.py
RUN make
RUN make install

FROM ubuntu:20.04
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libbotan-2-dev  

COPY --from=builder /usr/bin/encryptcli .