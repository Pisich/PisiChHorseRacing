# PisiChHorseBetting
By Carlos Rodríguez (Pisich)

A horse race betting simulator where the user can choose to bet for their favorite horse. PisiChHorseRacing uses all kinds of data structures for its internal operation, it features the use of Linked Lists, Heaps, HashMaps, etc. The user can also choose to add or remove horses, the difficulty of the race (easy or hard), the harder the difficulty is, the more obstacles the horse will have to jump. This version supports multithreading and memory management.

## Compiling
You can use any C compiler for this proyect, but I recommend you to use GCC.
```bash
# Clone the PisiChHorseRacing repo
git clone https://github.com/Pisich/PisiChHorseRacing

# Cd into the newly created folder
cd PisiChHorseRacing

# Compile the code
gcc -o main.c PisiChHorseRacing
```
## Building the container
To build the container you must have docker installed in your system.</br>
If you already have it you can just follow these steps to build the container:
```bash
# Clone the PisiChHorseRacing repo
git clone https://github.com/Pisich/PisiChHorseRacing

# Cd into the newly created folder
cd PisiChHorseRacing

# Build the container (Attention to the '.')
docker build -t pisichhorseracing:1.0 .

#Run the container
docker run pisichhorseracing:1.0
```
The proyect is built inside an Alpine image. Inside it, there are some basic compiling and formatting tools that the proyect depends on.
## Contributions
If you would like to see a feature added, feel free to submit an issue or a pull request.
