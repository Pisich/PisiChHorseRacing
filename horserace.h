#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#ifndef PISICH_RACE

#define RACE_LIM 50

#ifndef Bool
  #define Bool short int
#endif

typedef struct Horse{
  int chosen, id, bett, place;
  char name[20];
}Horse;

typedef struct RaceParams{
  int race[RACE_LIM];
}RaceParams;

typedef struct HorseList{
  Horse val;
  struct HorseList *nxt;
}HorseList;

typedef struct User{
  char name[50];
  int h_place, user_id, bett;
}User;

typedef struct UserList{
  User val;
  struct UserList *nxt;
}UserList;

typedef struct HashMap{
  int size;
  UserList **map;
}HashMap;

typedef struct Node{
  Horse val;
  struct Node *right, *left;
}Node;

typedef struct Heap{
  int size;
  Node *root;
  Horse *arr;
}Heap;
#endif
