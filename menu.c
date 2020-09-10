#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct Horse{
  int chosen;
  int id,bet,rep;
  int path[100];
  char name[20];
}Horse;

void * init_horse0(void *vargs){
  struct Horse Beautiful_Princess;
  Beautiful_Princess.chosen = 1;
  Beautiful_Princess.id = 0;
  printf("Beautiful Princess is ready!\n");
  pthread_exit(NULL);
}

void * init_horse1(void *vargs){
  struct Horse Pisich;
  Pisich.chosen = 1;
  Pisich.id = 1;
  printf("Pisich is ready!\n");
  pthread_exit(NULL);
}

void * init_horse2(void *vargs){
  struct Horse Carry;
  Carry.chosen = 1;
  Carry.id = 2;
  printf("Carry is ready!\n");
  pthread_exit(NULL);
}
void * init_horse3(void *vargs){
  struct Horse Jose;
  Jose.chosen = 1;
  Jose.id = 3;
  printf("Jose is ready!\n");
  pthread_exit(NULL);
}

void * init_horse4(void *vargs){
  struct Horse Kings_Son;
  Kings_Son.chosen = 1;
  Kings_Son.id = 4;
  printf("King's Son is ready!\n");
  pthread_exit(NULL);
}

void initial_print(){
  printf("WELCOME TO HORSE RACE SIM 2020\n");
  printf("Select the horse that you want to bet to!\n");
  printf("0. Beatiful Princess\n");
  printf("1. Pisich\n2. Carry\n3. Jose\n4. King's Son\n");
  printf("Enter your selection here: ");
}

int main() {
  char *option;
  pthread_t MyThread[5];
  const int PID[5] = {0,1,2,3,4};

  initial_print();
  //ARREGLO DE FUNCIONES PARA INICIALIZAR CABALLOS AQUI
  scanf("%c", option);

  switch(*option){
    case '0': pthread_create(&MyThread[0], NULL, init_horse0, NULL);
    pthread_join(MyThread[0], NULL);
    case '1': pthread_create(&MyThread[1], NULL, init_horse1, (void *)&PID[1]);
    pthread_join(MyThread[1], NULL);
    case '2': pthread_create(&MyThread[2], NULL, init_horse2, (void *)&PID[2]);
    pthread_join(MyThread[2], NULL);
    case '3': pthread_create(&MyThread[3], NULL, init_horse3, (void *)&PID[3]);
    pthread_join(MyThread[3], NULL);
    case '4': pthread_create(&MyThread[4], NULL, init_horse4, (void *)&PID[4]);
    pthread_join(MyThread[4], NULL);
  }
  return 0;
}