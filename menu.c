#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define RACE_LIM 50

typedef struct Horse{
  int chosen;
  int id,bet,rep;
  char path[RACE_LIM];
  char name[20];
}Horse;

typedef struct RaceParams{
  int race[RACE_LIM];
  struct Horse horses[4];
}RaceParams;

void * (*Func)(void *);

int *easy_race[RACE_LIM];
int *hard_race[RACE_LIM];


void * easy_diff(void *vargs){
  for(int i = 0; i<=RACE_LIM/5;i+=5) *easy_race[i] = rand() % 3;
  pthread_exit(NULL);
}

void * hard_diff(void *vargs){
  for(int i = 0; i<=RACE_LIM/3;i+=3) *easy_race[i] = rand() % 3;
  pthread_exit(NULL);
}

void * init_horses(void *vargs){
  int *chosen_or_n = (int *)vargs;

  struct Horse Beautiful_Princess;
  Beautiful_Princess.id = 0;
  strcpy(Beautiful_Princess.name, "Beautiful Princess");
  printf("Beautiful Princess is ready to race!\n");

  struct Horse Pisich;
  Pisich.id = 1;
  strcpy(Pisich.name, "Pisich");
  printf("Pisich is ready to race!\n");

  struct Horse Carry;
  Carry.id = 2;
  strcpy(Carry.name, "Carry");
  printf("Carry is ready to race!\n");

  struct Horse Jose;
  Jose.id = 3;
  strcpy(Jose.name, "Jose");
  printf("Jose is ready to race!\n");

  struct Horse Kings_Son;
  Kings_Son.id = 4;
  strcpy(Kings_Son.name, "Kings_Son");
  printf("King's Son is ready to race!\n");

  if(*chosen_or_n == 0) Beautiful_Princess.chosen = 1;
  else if(*chosen_or_n == 1) Pisich.chosen = 1;
  else if(*chosen_or_n == 2) Carry.chosen = 1;
  else if(*chosen_or_n == 3) Jose.chosen = 1;
  else if(*chosen_or_n == 4) Kings_Son.chosen = 1;

  pthread_exit(NULL);
}

void initial_print(){
  printf("WELCOME TO HORSE RACE SIM 2020\n");
  printf("Select the horse that you want to bet to!\n");
  printf("0. Beatiful Princess\n");
  printf("1. Pisich\n2. Carry\n3. Jose\n4. King's Son\n");
  printf("Enter your selection here: ");
}

void diff_print(){
  printf("Which race difficulty do you want to play?\n");
  printf("0. EASY\n1. HARD\n");
  printf("Please enter your selection: ");
}

int main() {
  int *option;
  int *easy_race[RACE_LIM], *hard_race[RACE_LIM] = {0};
  pthread_t MyThread[10];
  const int PID[5] = {0,1,2,3,4};

  srand(time(0));
  initial_print();
  
  scanf("%d", option);
  Func = &init_horses;
  switch(*option){
    case 0: pthread_create(&MyThread[0], NULL, Func, (void *)&PID[0]);
    pthread_join(MyThread[0], NULL);
    break;
    case 1: pthread_create(&MyThread[1], NULL, Func, (void *)&PID[1]);
    pthread_join(MyThread[1], NULL);
    break;
    case 2: pthread_create(&MyThread[2], NULL, Func, (void *)&PID[2]);
    pthread_join(MyThread[2], NULL);
    break;
    case 3: pthread_create(&MyThread[3], NULL, Func, (void *)&PID[3]);
    pthread_join(MyThread[3], NULL);
    break;
    case 4: pthread_create(&MyThread[4], NULL, Func, (void *)&PID[4]);
    pthread_join(MyThread[4], NULL);
    break;
  }
  pthread_create(&MyThread[5], NULL, easy_diff, (void *)&PID[0]);
  pthread_join(MyThread[5], NULL);
  pthread_create(&MyThread[6], NULL, hard_diff, (void*)&PID[0]);
  pthread_join(MyThread[6], NULL);

  diff_print();
  scanf("%d",option);
  
  for(int i = 0;i<RACE_LIM;i++) printf("%d", *easy_race[i]);
  printf("\n\n");
  for(int i = 0;i<RACE_LIM;i++) printf("%d", *hard_race[i]);
  return 1;
}