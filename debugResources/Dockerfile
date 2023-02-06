# Dockerfile that does not clone git repo when built, useful when working locally

FROM alpine:latest

WORKDIR /usr/src/PisiCh_HorseRacing

COPY . .

RUN apk add gcc libc-dev\
  && gcc -pthread -o PisiChHorseRacing main.c

ENTRYPOINT ["./PisiChHorseRacing"]
