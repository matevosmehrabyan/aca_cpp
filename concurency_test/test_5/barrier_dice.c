#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_barrier_t barrier;
pthread_mutex_t mutex;

// pthread_mutex_lock(&mutex);
// pthread_mutex_unlock(&mutex);


#define NUM_THREADS 5
int dices[NUM_THREADS];

void do_A() { printf("Doing A\n"); }
void do_B() { printf("Doing B\n"); }

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    while (1) {
        int random_number = (rand() % 6) + 1;
        printf("Thread %d: Rolled a %d\n", thread_id, random_number);
        dices[thread_id] = random_number;
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
    }
}

void* decision_maker () {
    while (1) {
        pthread_mutex_lock(&mutex);
        pthread_barrier_wait(&barrier);
        int winner = 0;
        for (int i = 0; i < NUM_THREADS; i++) {
            if (dices[i] > dices[winner]) {
                winner = i;
            }
        }

        printf("Thread %d wins with Value %d\n", winner, dices[winner]);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}


int main() {
    if (pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1) != 0) {
        perror("pthread_barrier_init");
        return EXIT_FAILURE;
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    pthread_t decision_thread;
    if (pthread_create(&decision_thread, NULL, decision_maker, NULL) != 0) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_join(decision_thread, NULL);
    // Destroy the barrier
    pthread_barrier_destroy(&barrier);

    return 0;
}
