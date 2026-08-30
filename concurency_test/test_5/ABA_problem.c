#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter1 = 0, counter2 = 0;
char var = 'a';


void do_A() { printf("Doing A\n"); }
void do_B() { printf("Doing B\n"); }


void* t1_work() {
  while (1) {
    if (var == 'a') {
      var = 'b';
    }
    else {
      var = 'a';
    }
    counter1++;
    sleep(1);
  }
}

void* t2_work() {
  void (*work)() = &do_A;

  while (1) {
    if (counter1 == counter2) {
      work();
      continue;
    }

    if (work == &do_A) {
      work = &do_B;
    }
    else {
      work = &do_A;
    }

    work();
    counter2++;
  }
}


int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, &t1_work, NULL) != 0) {
        printf("Thread 1 failed!");
        return 1;
    }

    if (pthread_create(&thread2, NULL, &t2_work, NULL) != 0) {
        printf("Thread 2 failed!");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
