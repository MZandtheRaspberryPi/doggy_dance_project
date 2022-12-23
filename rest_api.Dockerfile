FROM alpine:3.17

RUN apk add git
RUN apk add cmake
RUN apk add g++
RUN apk add make
RUN apk add eigen eigen-dev

RUN git clone https://github.com/oatpp/oatpp.git && cd oatpp/ && mkdir build && cd build && cmake .. && make install

COPY ./ ./app

RUN cd /app && mkdir build && cd build && cmake .. && make

ENTRYPOINT ["/app/build/doggy-dance-project-exe"]
