# PisiChHorseRacing
By Carlos Rodríguez (Pisich)

A horse race betting simulator where the user can choose to bet for their favorite horse. PisiChHorseRacing only uses data structures for its internal operation, it features linked lists, heaps, hashmaps, etc. The user can choose to add and remove horses, the difficulty of the race (easy or hard), the harder the difficulty is, the more obstacles the horse will have to jump.
This project uses multithreading and dynamic memory management for its internal functioning.

## Compiling
You can use any C compiler for this proyect, but I recommend you to use GCC.
```bash
# Clone the PisiChHorseRacing repo
git clone https://github.com/Pisich/PisiChHorseRacing .

# Compile the code
gcc -o -pthread main.c PisiChHorseRacing 
```
## Building the container
To build the container you must have Docker installed in your system.</br>
If you already have it you can just follow these steps to build the container:
```bash
# Clone the PisiChHorseRacing repo
git clone https://github.com/Pisich/PisiChHorseRacing .

# Build the container
docker build -t pisichhorseracing:1.0 .

#Run the container
docker run -it pisichhorseracing:1.0
```
The proyect is built inside an Alpine image. Inside it, there are some basic compiling and formatting tools that the proyect depends on.
## Contributions
If you would like to see a feature added, feel free to submit an issue or a pull request.
