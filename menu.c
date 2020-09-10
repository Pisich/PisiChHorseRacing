#include <stdio.h>
#include <pthread.h>
#include <time.h>

void * option0(void *vargs){
  printf("OPTION 0");
  pthread_exit(NULL);
}

void * option1(void *vargs){
  printf("OPTION 1");
  pthread_exit(NULL);
}

void * option2(void *vargs){
  printf("OPTION 2");
  pthread_exit(NULL);
}
void * option3(void *vargs){
  printf("OPTION 3");
  pthread_exit(NULL);
}

void * option4(void *vargs){
  printf("OPTION 4");
  pthread_exit(NULL);
}

void initial_print(){
  printf("INITIAL PRINT + OPTIONS\n");
}

int main() {
  char *option;
  pthread_t MyThread[5];
  const int PID[5] = {0,1,2,3,4};

  initial_print();

  scanf("%c", option);

  switch(*option){
    case 0: pthread_create(&MyThread[0], NULL, option0, (void *)&PID[0]);
    pthread_join(MyThread[0], NULL);
    case 1: pthread_create(&MyThread[1], NULL, option1, (void *)&PID[1]);
    pthread_join(MyThread[1], NULL);
    case 2: pthread_create(&MyThread[2], NULL, option2, (void *)&PID[2]);
    pthread_join(MyThread[2], NULL);
    case 3: pthread_create(&MyThread[3], NULL, option3, (void *)&PID[3]);
    pthread_join(MyThread[3], NULL);
    case 4: pthread_create(&MyThread[4], NULL, option4, (void *)&PID[4]);
    pthread_join(MyThread[4], NULL);
    default:  initial_print();
  }
  return 0;
}