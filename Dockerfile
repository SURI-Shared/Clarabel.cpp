FROM rust

RUN apt-get install cmake

WORKDIR /src/Clarabel.cpp
COPY . .
WORKDIR /src/Clarabel.cpp/build
RUN cmake /src/Clarabel.cpp
RUN make