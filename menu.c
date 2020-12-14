#include "horserace.h"

#define RACE_LIM 50
#define MAX_MAP_SIZE 5
//Pointer to function
void * (*Func)(void *);
typedef void (*adv_or_dis)(int);
// Easy and Hard tracks
int easy_race[RACE_LIM];
int hard_race[RACE_LIM];
// Flags
int start = 0;
int end = 0;
int bet = 0;
int top = 0;
int player = 1;
int repeat = 0;
// Global parameters
RaceParams *RaceGen;
HorseList *horse_head;
HorseList *heady;
HashMap *db;

char last_winner[50] = {0};
char usernames[5][50] = {0};
int bets[5] = {0};
int num_users;
// Horse names list
char names[15][20] = {"Rusher", "Gotcha", "White J", "Bones", "Sentinel", "Beautiful Princess", "Pancreas", "Carry", "Kings Son", "Jose", "Carnage", "Corn Breaker"};

UserList * initUNode(char val[]){
  UserList *neww = malloc(sizeof(UserList));
  strcpy(neww->val.name, val);
  neww->nxt = NULL;
  return neww;
}

HorseList * iterList(int places){
  HorseList *head = horse_head;
  for(int i =0;i<places;i++) head = head->nxt;
  return head;
}

HashMap * MapCreate(HashMap *Hmap, int size){
  Hmap = malloc(sizeof(HashMap));
  Hmap->map = malloc(sizeof(UserList)*size);
  for(int i=0;i<size;i++) Hmap->map[i] = NULL;
  Hmap->size = 0;
  return Hmap;
}

void bet_amount(int place, User userr, int id){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  printf("%s place your bet for %s: ", userr.name, head->val.name);
  scanf("%d", &bet);
  while(bet < 0){
    printf("Invalid answer, please try again: ");
    scanf("%d", &bet);
  }
  bets[id-1] = bet;
  strcpy(usernames[id-1], userr.name);
  head->val.bett = bet;
}

void horse_trip(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen >= 1)
    printf("\n%s tripped!\n", head->val.name);
  sleep(2);
}

void horse_jump(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen >= 1)
    printf("\n%s got boosted!\n", head->val.name);
}

void horse_stuck(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen >= 1)
    printf("\n%s got stuck!\n", head->val.name);
  sleep(rand() % 3);
}

void horse_fell(int place){
  HorseList *head = horse_head;
  for(int i=0;i<place;i++) head = head->nxt;
  if(head->val.chosen >= 1)
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

void add_and_init_horse(){
  HorseList *head = horse_head;
  HorseList *neww = malloc(sizeof(HorseList));
  neww->val.id = top;
  strcpy(neww->val.name, names[top]);
  while(head->nxt != NULL) head = head->nxt;
  head->nxt = neww;
  top++;
}

void * init_horses(void *vargs){
  int *chosen_or_n = (int *)vargs;
  HorseList *head = horse_head;
  for(int i = 0; i< *chosen_or_n; i++) head = head->nxt;
  head->val.chosen = player;
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

void initial_print(){
  HorseList *head = horse_head;
  printf("WELCOME TO HORSE RACE SIM 2020\n");
  printf("Select the horse that you want to bet to!\n");
  for(int i=0;i<top;i++){
    printf("%d. %s\n", i, head->val.name);
    head = head->nxt;
  }
  printf("Enter your selection here: ");
}

void freeHeap(Node *root){
  if(root != NULL){
    if(root->left != NULL) freeHeap(root->left);
    if(root->right != NULL) freeHeap(root->right);
    free(root);
  }
}

Horse HorsePeek(Node *root){
  return root->val;
}

void reset(){
  top = 0;
  start = 0;
  end = 0;
  bet = 0;
  player = 1;
  repeat = 1;
  HorseList *temp;
  for(int i=0; i<top; i++){
    temp = horse_head->nxt;
    free(horse_head);
    horse_head = temp;
  }
  for(int i=0;i<5;i++) bets[i] = 0;
  for(int i=0;i<5;i++) strcpy(usernames[i], "");
  free(RaceGen);
  RaceGen = NULL;
  horse_head = NULL;
  heady = NULL;
  Func = NULL;
}

void leaderboard(){
  Horse winner = HorsePeek(last_match->root);
  printf("\tLeaderboard:\n");
  printf("\n\n\t%s won last match\n", last_winner);
}

int main_menu(){
  int option;
  printf("Pre-race options:\n");
  if(top == 5) printf("Enter 0 to play with default settings (5 horses)\n");
  else printf("Enter 0 to exit\n");
  printf("1. Add a horse\n2. Remove a horse\n");
  if(repeat) printf("3. See last match winner\n");
  printf("Enter your selection here: ");
  scanf("%d", &option);
  if(top == 12 && option == 1){
    printf("Reached max amount of horses in a race!\n\n");
    return 0;
  }
  else if(top == 2 && option == 2){
    printf("You can't have less than 2 horses in the track!\n\n");
    return 0;
  }
  else if(option == 3) leaderboard();
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

int playAgain(){
  char option;
  scanf("%c", &option);
  printf("Would you like to race again? (y or n): ");
  scanf("%c", &option);
  while(option != 'y' && option != 'n'){
    printf("Invalid answer, please try again\n");
    printf("Would you like to race again? (y or n): ");
    scanf("%c", &option);
  }
  if(option == 'y') return 1;
  else return 0;
}

int Hash_CERC(char str[]){
  int len = strlen(str);
  unsigned long int key = str[0];
  int pos = 1;
  for(int i=0; i < len; i++){
    key += key * pow(26,len-1) + str[pos];
    pos++;
  }
  return key % MAX_MAP_SIZE;
}

User MapInsert(HashMap *Hmap, char str[]){
  int key = Hash_CERC(str);
  if(Hmap->map[key] == NULL){
    Hmap->map[key] = initUNode(str);
    return Hmap->map[key]->val;
  }
  else{
    UserList *temp = Hmap->map[key];
    while(temp->nxt != NULL) temp = temp->nxt;
    temp->nxt = initUNode(str);
    return temp->nxt->val;
  }
}

Bool MapContains(HashMap *Hmap, char str[]){
  for(int i=0;i < Hmap->size;i++){
    if(Hmap->map[i] != NULL){
      if(strcmp(Hmap->map[i]->val.name, str) == 0){
        printf("Found user '%s' in Database\n", str);
        return 1;
      }
      UserList *temp = Hmap->map[i];
      while(temp->nxt != NULL){
        if(strcmp(temp->val.name, str) == 0){
          printf("Found user '%s' in Database\n", str);
          return 1;
        }
        temp = temp->nxt;
      }
    }
  }
  printf("This HashMap does not contain the user '%s', creating new user\n", str);
  return 0;
}

User MapGets(HashMap *Hmap, char str[]){
  int key = Hash_CERC(str);
  if(Hmap->map[key] != NULL){
    if(strcmp(Hmap->map[key]->val.name, str) == 0) return Hmap->map[key]->val;
    UserList *temp = Hmap->map[key];
    while(temp->nxt != NULL){
      if(strcmp(temp->val.name, str) == 0) return temp->val;
    }
  }
  User null_str;
  return null_str;
}

void pay_bets(){
  for(int i=0;i<num_users;i++){
    if(bets[i]){
      User userr = MapGets(db, usernames[i]);
      HorseList *my_horse = iterList(userr.h_place);
      if(my_horse->val.place <= 0) printf("%s won his/her $%d bet!\n\n", userr.name, bets[i]);
      else printf("%s lost his/her $%d bet\n\n", userr.name, bets[i]);
    }
  }
}

int UserAsk(){
  int num;
  printf("How many players are playing right now? ");
  scanf("%d", &num);
  while(num > 5 || num < 0){
    printf("Invalid entry, please try again: ");
    scanf("%d", &num);
  }
  return num;
}

int main() {
  int f;
  int *option = &f;
  pthread_t MyThread[12];
  const int PID[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
  RaceGen = malloc(sizeof(RaceParams));

  horse_head = malloc(sizeof(HorseList));
  horse_head->nxt = NULL;
  strcpy(horse_head->val.name, names[11]);

  if(!repeat) db = MapCreate(db, 5);

  srand(time(0));
  for(int i = 0;i<5;i++) add_and_init_horse();
  while( (f = main_menu()) != 0){
    switch(f){
    case 1: add_and_init_horse();
    break;
    case 2: remove_horse();
    break;
    case 3: break;
    } 
  }

  Func = &init_horses;
  // Users enter their name and horse selection
  num_users = UserAsk();
  char temp[50];
  heady = horse_head;

  for(int i=1;i<num_users+1;i++){
    printf("User %d please enter your name: ", i);
    scanf("%s", temp);
    User userr;
    if(!MapContains(db, temp)) userr = MapInsert(db, temp);
    else userr = MapGets(db, temp);
    userr.user_id = i;
    printf("\t%s please enter your selection:\n\n", temp);
    initial_print();
    scanf("%d", option);
    while(*option > top-1 || *option < 0 || iterList(*option)->val.chosen >= 1){
      printf("Invalid answer, please try again: ");
      scanf("%d", option);
    }

    player = i;

    pthread_create(&MyThread[i], NULL, Func, (void *) option);
    pthread_join(MyThread[i], NULL);

    bet_amount(*option, userr, userr.user_id);
  }

  // Track creation
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
  // Create all horse threads
  int i = 0;
  while(heady->nxt != NULL){
    pthread_create(&MyThread[i], NULL, race, (void *)&PID[i]);
    heady = heady->nxt;
    i++;
  }
  // Set 'start' flag on 1 to start race
  start = 1;
  i = 0;
  heady = horse_head;
  // Wait for all horse threads to finish the race
  while(heady->nxt != NULL){
    pthread_join(MyThread[i], NULL);
    heady = heady->nxt;
    i++;
  }

  printf("\n\nTHE RACE ENDED!\n");
  // Pay the player bets
  pay_bets();
  // Free the last min heap
  // If the user wants to play again, the program performs a reset
  heady = horse_head;
  if(playAgain()){
    while(heady->nxt != NULL){
      if(heady->val.place == 1) strcpy(last_winner, heady->val.name);
      heady = heady->nxt;
    }
    reset();
    main();
  }
  free(RaceGen);
  return 0;
}
