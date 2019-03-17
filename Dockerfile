FROM alpine:3.9

RUN apk add build-base boost-dev libpng-dev

RUN mkdir image-it

WORKDIR image-it

COPY app src/

RUN g++ -v -std=c++14 -O2 -o image-it \
    -lpng \
    -lz \
    ./src/main.cpp \
    `libpng-config --ldflags`

CMD ["./image-it"]
