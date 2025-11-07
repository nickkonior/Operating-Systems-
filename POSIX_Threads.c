#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 3

sem_t semaphores[NUM_THREADS];

typedef struct {
    int thread_id;
    char *value;
} ThreadData;

void *thread_function(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int thread_id = data->thread_id;
    char *value = data->value;

    while (1) {
        sem_wait(&semaphores[thread_id]);
        printf("<%s>", value);
        fflush(stdout);
        usleep(10);  // Sleep for 1 second
        sem_post(&semaphores[(thread_id + 1) % NUM_THREADS]);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int i, result;

    // Initialize semaphores
    for (i = 0; i < NUM_THREADS; ++i) {
        result = sem_init(&semaphores[i], 0, 0);
        if (result != 0) {
            perror("Semaphore initialization failed");
            exit(EXIT_FAILURE);
        }
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].thread_id = i;
        if (i == 0)
            thread_data[i].value = "one";
        else if (i == 1)
            thread_data[i].value = "two";
        else if (i == 2)
            thread_data[i].value = "three";

        result = pthread_create(&threads[i], NULL, thread_function, &thread_data[i]);
        if (result != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Start with the first thread
    sem_post(&semaphores[0]);

    // Wait for threads to finish (will never happen in this example)
    for (i = 0; i < NUM_THREADS; ++i) {
        result = pthread_join(threads[i], NULL);
        if (result != 0) {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy semaphores
    for (i = 0; i < NUM_THREADS; ++i) {
        result = sem_destroy(&semaphores[i]);
        if (result != 0) {
            perror("Semaphore destruction failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
