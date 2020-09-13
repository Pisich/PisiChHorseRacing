#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RACE_LIM 50

typedef struct Horse{
  int chosen, id;
  char name[20];
}Horse;

typedef struct RaceParams{
  int race[RACE_LIM];
  struct Horse horses[5];
}RaceParams;

void * (*Func)(void *);
typedef void (*adv_or_dis)(int);

int easy_race[RACE_LIM];
int hard_race[RACE_LIM];
int start = 0;
int end = 0;

struct RaceParams *RaceGen;


void horse_trip(int place){
  if(RaceGen->horses[place].chosen == 1)
    printf("\n%s tripped!\n", RaceGen->horses[place].name);
  sleep(2);
}

void horse_jump(int place){
  if(RaceGen->horses[place].chosen == 1)
    printf("\n%s got boosted!\n", RaceGen->horses[place].name);
}

void horse_stuck(int place){
  if(RaceGen->horses[place].chosen == 1)
    printf("\n%s got stuck!\n", RaceGen->horses[place].name);
  sleep(rand() % 3);
}

void horse_fell(int place){
  if(RaceGen->horses[place].chosen == 1)
    printf("\n%s fell!\n", RaceGen->horses[place].name);
  sleep(rand() % 5);
}
void * easy_diff(void *vargs){

  for(int i = 0; i<RACE_LIM;i+=5) easy_race[i] = rand() % 4;
  pthread_exit(NULL);
}

void * hard_diff(void *vargs){

  for(int i = 0; i<RACE_LIM;i+=3) hard_race[i] = rand() % 4;
  pthread_exit(NULL);
}

void * init_horses(void *vargs){
  int *chosen_or_n = (int *)vargs;

  struct Horse Beautiful_Princess;
  Beautiful_Princess.id = 0;
  strcpy(Beautiful_Princess.name, "Beautiful Princess");
  printf("%s is ready to race!\n", Beautiful_Princess.name);

  struct Horse Pisich;
  Pisich.id = 1;
  strcpy(Pisich.name, "Pisich");
  printf("%s is ready to race!\n", Pisich.name);

  struct Horse Carry;
  Carry.id = 2;
  strcpy(Carry.name, "Carry");
  printf("%s is ready to race!\n", Carry.name);

  struct Horse Jose;
  Jose.id = 3;
  strcpy(Jose.name, "Jose");
  printf("%s is ready to race!\n", Jose.name);

  struct Horse Kings_Son;
  Kings_Son.id = 4;
  strcpy(Kings_Son.name, "Kings_Son");
  printf("%s is ready to race!\n", Kings_Son.name);

  if(*chosen_or_n == 0) Beautiful_Princess.chosen = 1;
  else if(*chosen_or_n == 1) Pisich.chosen = 1;
  else if(*chosen_or_n == 2) Carry.chosen = 1;
  else if(*chosen_or_n == 3) Jose.chosen = 1;
  else if(*chosen_or_n == 4) Kings_Son.chosen = 1;
  
  RaceGen->horses[0] = Beautiful_Princess;
  RaceGen->horses[1] = Pisich;
  RaceGen->horses[2] = Carry;
  RaceGen->horses[3] = Jose;
  RaceGen->horses[4] = Kings_Son;
  
  pthread_exit(NULL);
}

void * race(void * horse){
  int *actual_horse = (int *)horse;
  while(! start);
  adv_or_dis advantage = horse_jump;
  adv_or_dis disadvantage1 = horse_trip;
  adv_or_dis disadvantage2 = horse_stuck;
  adv_or_dis disadvantage3 = horse_fell;
  for(int i = 0;i<RACE_LIM;i++){
    if(RaceGen->race[i] == 1){
      disadvantage1(*actual_horse);
    }
    else if(RaceGen->race[i] == 2){
      advantage(*actual_horse);
      i++;
    }
    else if(RaceGen->race[i] == 3){
      disadvantage2(*actual_horse);
    }
    else if(RaceGen->race[i] == 4){
      disadvantage3(*actual_horse);
    }
  }
  end ++;
  printf("\n%s got %d place!\n", RaceGen->horses[*actual_horse].name, end);
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

void pre_race_print(){
  printf("Race is about to start!\n");
  printf("Grab your popcorn and good luck to everybody!\n");
  printf("\n\nSTART\n\n");
}

int main() {
  int *option;
  pthread_t MyThread[10];
  const int PID[5] = {0,1,2,3,4};
  RaceGen = malloc(sizeof(RaceParams));
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
  pthread_create(&MyThread[6], NULL, hard_diff, (void *)&PID[0]);
  pthread_join(MyThread[6], NULL);

  diff_print();
  scanf("%d",option);
  switch(*option){
    case 0: for(int i= 0;i<RACE_LIM;i++) RaceGen->race[i] = easy_race[i];
    break;
    case 1: for(int i= 0;i<RACE_LIM;i++) RaceGen->race[i] = hard_race[i];
    break;
  }
  pre_race_print();
  for(int i = 0; i<5;i++) pthread_create(&MyThread[i], NULL, race, (void *)&PID[i]);

  start = 1;
  
  for(int i= 0; i<5;i++) pthread_join(MyThread[i], NULL);

  printf("\n\nTHE RACE ENDED!\n");
  return 1;
}