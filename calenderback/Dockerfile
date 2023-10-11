FROM ubuntu:latest

# dev essential tools for ubuntu

RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    cmake \
    curl \
    git \
    libcurl4-openssl-dev \
    python3 \
    libpq-dev

RUN mkdir /calenderback
WORKDIR /calenderback

COPY . /calenderback

# build folder build
RUN mkdir build
WORKDIR /calenderback/build
RUN cmake ..
RUN make

WORKDIR /calenderback/build
CMD ["./calenderback"]