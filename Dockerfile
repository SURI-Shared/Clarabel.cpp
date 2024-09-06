FROM rust

RUN apt-get update
RUN apt-get install -qq cmake

WORKDIR /src
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
RUN tar xf /src/eigen-3.4.0.tar.gz
WORKDIR /src/eigen-3.4.0/build
RUN cmake .. -DCMAKE_BUILD_TYPE=Release
RUN make install

WORKDIR /src/Clarabel.cpp
COPY Clarabel.rs Clarabel.rs
COPY examples examples
COPY include include
COPY rust_wrapper rust_wrapper
COPY tests tests
COPY CMakeLists.txt CMakeLists.txt
WORKDIR /src/Clarabel.cpp/build
RUN cmake /src/Clarabel.cpp -DCMAKE_BUILD_TYPE=Release
RUN make