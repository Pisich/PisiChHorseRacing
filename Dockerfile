FROM alpine:3.12

RUN apk add figlet && apk add build-base && apk add git

CMD git clone https://github.com/Pisich/PisiChHorseRacing ; cd PisiChHorseRacing/ ; gcc -pthread -o PisiChHorseRacing menu.c ; ./PisiChHorseRacing
