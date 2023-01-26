FROM alpine:latest

RUN apk add figlet gcc git

CMD git clone https://github.com/Pisich/PisiChHorseRacing .; gcc -pthread -o PisiChHorseRacing main.c ; ./PisiChHorseRacing
