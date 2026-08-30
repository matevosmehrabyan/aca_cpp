#include <stdio.h>
#include <pthread.h>

int  t1_want = 0, t2_want = 0;
int Favored = 1;
int x = 5;

void* tr1() {
  while (1) {
    t1_want = 1;
    Favored = 2;
  
    while (t2_want && Favored == 2);
  
    x--;
    printf("aaaa %d\n", x);
    x++;
    t1_want = 0;
  }
}


void* tr2() {
  while (1) {
    t2_want = 1;
    Favored = 1;
  
    while (t1_want && Favored == 1);
  
    x++;
    printf("bbbb %d\n", x);
    x--;
    t2_want = 0;
  }
}

int main () {
  pthread_t thread1, thread2;

  
  if (pthread_create(&thread1, NULL, &tr1, NULL) != 0) {
    perror("Failed to create thread");
    return 1;
  }

  if (pthread_create(&thread2, NULL, &tr2, NULL) != 0) {
    perror("Failed to create thread");
    return 1;
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
