#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RACE_LIM 50

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

void * (*Func)(void *);
typedef void (*adv_or_dis)(int);

int easy_race[RACE_LIM];
int hard_race[RACE_LIM];
int start = 0;
int end = 0;
int bet = 0;

RaceParams *RaceGen;
HorseList *horse_head;
HorseList *heady;
int top = 0;
char names[15][20] = {"Rusher", "Gotcha", "White J", "Bones", "Sentinel", "Beautiful Princess", "Pisich", "Carry", "Kings Son", "Jose", "Carnage", "Corn Breaker"};

void bet_amount(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  printf("Place your bet for %s: ", head->val.name);
  scanf("%d", &bet);
  head->val.bett = bet;
}

void horse_trip(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen == 1)
    printf("\n%s tripped!\n", head->val.name);
  sleep(2);
}

void horse_jump(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen == 1)
    printf("\n%s got boosted!\n", head->val.name);
}

void horse_stuck(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen == 1)
    printf("\n%s got stuck!\n", head->val.name);
  sleep(rand() % 3);
}

void horse_fell(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen == 1)
    printf("\n%s fell!\n", head->val.name);
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

void add_and_init_horse(HorseList *head){
  HorseList *neww = malloc(sizeof(HorseList));
  neww->val.id = top;
  strcpy(neww->val.name, names[top]);
  while(head->nxt != NULL) head = head->nxt;
  head->nxt = neww;
  top++;
}

void * init_horses(void *vargs){
  int *chosen_or_n = (int *)vargs;
  int i = 0;
  HorseList *head = horse_head;
  while(i<*chosen_or_n){
    head = head->nxt;
    i++;
  }
  head->val.chosen = 1;
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
  HorseList *head = horse_head;
  for(int i=0;i<*actual_horse;i++) head = head->nxt;
  head->val.place = end;
  printf("\n\t%s got %d place!\n", head->val.name, end);
  pthread_exit(NULL);
}

void remove_horse(){
  HorseList *temp_head = horse_head;
  while(temp_head->nxt->nxt != NULL){
    temp_head = temp_head->nxt;
  }
  temp_head->nxt = NULL;
  top--;
}

void initial_print(HorseList *head){
  printf("WELCOME TO HORSE RACE SIM 2020\n");
  printf("Select the horse that you want to bet to!\n");
  for(int i=0;i<top;i++){
    printf("%d. %s\n", i, head->val.name);
    head = head->nxt;
  }
  printf("Enter your selection here: ");
}

int main_menu(){
  int option;
  printf("Pre-race options:\n");
  if(top == 0) printf("Enter 0 to play with default settings\n");
  else printf("Enter 0 to exit\n");
  printf("1. Add a horse (Default is 5)\n2. Remove a horse (Default is 5)\n");
  printf("Enter your selection here: ");
  scanf("%d", &option);
  return option;
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
  int f;
  pthread_t MyThread[10];
  const int PID[10] = {0,1,2,3,4,5,6,7,8,9};
  RaceGen = malloc(sizeof(RaceParams));

  horse_head = malloc(sizeof(HorseList));
  horse_head->nxt = NULL;
  strcpy(horse_head->val.name, names[11]);

  srand(time(0));
  for(int i = 0;i<5;i++) add_and_init_horse(horse_head);
  while( (f = main_menu()) != 0){
    switch(f){
    case 1: add_and_init_horse(horse_head);
    break;
    case 2: remove_horse();
    break;
    } 
  }
  initial_print(horse_head);
  scanf("%d", option);

  Func = &init_horses;
  heady = horse_head;
  int i;
  for(i =0 ;i<*option;i++) heady = heady->nxt;
  pthread_create(&MyThread[i], NULL, Func, (void *)&PID[i]);
  pthread_join(MyThread[i], NULL);
  bet_amount(PID[i]);

  /*Track creation*/
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
  heady = horse_head;

  i =0;
  while(heady->nxt != NULL){
    pthread_create(&MyThread[i], NULL, race, (void *)&PID[i]);
    heady = heady->nxt;
    i++;
  }

  start = 1;
  i = 0;
  heady = horse_head;
  while(heady->nxt != NULL){
    pthread_join(MyThread[i], NULL);
    heady = heady->nxt;
    i++;
  }

  printf("\n\nTHE RACE ENDED!\n");
  heady = horse_head;
  while(heady->nxt != NULL){
    if(heady->val.chosen == 1){
      if(heady->val.place == 1)
        printf("You won your %d bet!\n", heady->val.bett);
      else printf("You lost your %d bet!\n", heady->val.bett);
    }
    heady = heady->nxt;
  }
  free(RaceGen);
  return 1;
}
