FROM rust

RUN apt-get update
RUN apt-get install -qq cmake

WORKDIR /src
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
RUN tar xf /src/eigen-3.4.0.tar.gz
WORKDIR /src/eigen-3.4.0/build
RUN cmake .. -DCMAKE_BUILD_TYPE=RELEASE
RUN make install

WORKDIR /src/Clarabel.cpp
COPY . .
WORKDIR /src/Clarabel.cpp/build
RUN cmake /src/Clarabel.cpp
RUN make