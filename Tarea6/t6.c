#include <pthread.h>

#include "t6.h"
// *** Esta implementacion no funciona porque no respeta orden de llegada ***

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c= PTHREAD_COND_INITIALIZER;
int ACTUAL_NUMBER = 1;
int LAST_NUMBER = 1;

void ocupar() {
  pthread_mutex_lock(&m);
  int this_number = LAST_NUMBER;
  LAST_NUMBER++;
  while (this_number > ACTUAL_NUMBER){
    pthread_cond_wait(&c,&m);
  }
  pthread_mutex_unlock(&m);
}

void desocupar() {
  pthread_mutex_lock(&m);
  ACTUAL_NUMBER++;
  pthread_cond_broadcast(&c);
  pthread_mutex_unlock(&m);  
}
