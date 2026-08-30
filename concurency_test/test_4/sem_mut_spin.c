#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_ITERATIONS 1000000
// Shared counter
volatile int counter = 0;
pthread_mutex_t mutex;           // Mutex
pthread_spinlock_t spinlock;     // Spinlock
sem_t semaphore;

// Function for incrementing the counter (Critical Section)
void *increment_counter_mutex(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *increment_counter_spinlock(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_spin_lock(&spinlock);
        counter++;
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

void *increment_counter_semaphore(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(&semaphore);
        counter++;
        sem_post(&semaphore);
    }
    return NULL;
}


void test_mutex() {
  counter = 0;
  pthread_t thread1, thread2;
    // Create two threads
  pthread_create(&thread1, NULL, increment_counter_mutex, NULL);
  pthread_create(&thread2, NULL, increment_counter_mutex, NULL);
  // Wait for threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  // Print the final value of the counter
  printf("Final Mutex Counter: %d\n", counter);
}

void test_spinlock() {
   if (pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE) != 0) {
    perror("Failed to initialize spinlock");
  }
  counter = 0;
  pthread_t thread1, thread2;
    // Create two threads
  pthread_create(&thread1, NULL, increment_counter_spinlock, NULL);
  pthread_create(&thread2, NULL, increment_counter_spinlock, NULL);
  // Wait for threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  // Print the final value of the counter
  printf("Final Spinlock Counter: %d\n", counter);
}

void test_semaphore() {
  if (sem_init(&semaphore, 0, 1) != 0) {
    perror("Failed to initialize semaphore");
  }
  counter = 0;
  pthread_t thread1, thread2;
    // Create two threads
  pthread_create(&thread1, NULL, increment_counter_semaphore, NULL);
  pthread_create(&thread2, NULL, increment_counter_semaphore, NULL);
  // Wait for threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  // Print the final value of the counter
  printf("Final Semaphore Counter: %d\n", counter);
}


int main() {
    test_mutex();
    test_semaphore();
    test_spinlock();
    
    return 0;
}
