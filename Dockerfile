FROM alpine:latest

WORKDIR /usr/src/PisiCh_HorseRacing

RUN apk add gcc git libc-dev\
  && git clone https://github.com/Pisich/PisiChHorseRacing .\
  && gcc -pthread -o PisiChHorseRacing main.c

ENTRYPOINT ["./PisiChHorseRacing"]
