FROM alpine:3.17 as restapi-build

RUN apk add git
RUN apk add cmake
RUN apk add g++
RUN apk add make
RUN apk add eigen eigen-dev

RUN git clone https://github.com/oatpp/oatpp.git && cd oatpp/ && mkdir build && cd build && cmake .. && make install

RUN rm -rf oatpp

COPY ./ ./app

RUN cd /app && mkdir build && cd build && cmake .. && make

RUN mkdir /entrypoint && cp /app/build/robo-dance-project-exe /entrypoint

RUN rm -rf /app

FROM alpine:3.17
RUN apk add cmake g++ make
COPY --from=restapi-build /entrypoint/robo-dance-project-exe /robo-dance-project-exe
EXPOSE 8000
ENTRYPOINT ["/robo-dance-project-exe"]
