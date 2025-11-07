#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int** array;
int num_lines;
int num_threads;
int* local_maxima;

void* thread_function(void* arg);

int main() {
    clock_t begin = clock();
    printf("Enter the number of lines: ");
    scanf("%d", &num_lines);

    printf("Enter the number of threads to create: ");
    scanf("%d", &num_threads);

    // Dynamically allocate memory for the array
    array = (int**)malloc(num_lines * sizeof(int*));
    for (int i = 0; i < num_lines; i++) {
        array[i] = (int*)malloc(num_lines * sizeof(int));
    }

    FILE* file = fopen("A.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
        exit(1);
    }
    // Read the array values from the file
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_lines; j++) {
            if (fscanf(file, "%d", &array[i][j]) != 1) {
                fprintf(stderr, "Failed to read array value at (%d, %d).\n", i, j);
                exit(1);
            }
        }
    }

    // Dynamically allocate memory for local_maxima array
    local_maxima = (int*)malloc(num_threads * sizeof(int));

    pthread_t threads[num_threads];

    // Create the specified number of threads
    for (int i = 0; i < num_threads; i++) {
        int* thread_num = malloc(sizeof(int));
        *thread_num = i;
        if (pthread_create(&threads[i], NULL, thread_function, thread_num) != 0) {
            fprintf(stderr, "Failed to create thread %d.\n", i);
            exit(1);
        }
    }

    // Wait for each thread to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    int overall_max = local_maxima[0];

    // Find the overall maximum among local maxima
    for (int i = 1; i < num_threads; i++) {
        if (local_maxima[i] > overall_max) {
            overall_max = local_maxima[i];
        }
    }

    printf("The overall maximum value in the array is: %d\n", overall_max);

    // Free allocated memory
    for (int i = 0; i < num_lines; i++) {
        free(array[i]);
    }
    free(array);
    free(local_maxima);

    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Runtime = %f",time_spent);

    return 0;
}

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    int start_line = thread_num * num_lines/num_threads;
    int end_line = start_line + num_lines/num_threads - 1;
    int local_max = array[start_line][0];

    for (int i = start_line; i <= end_line; i++) {
        for (int j = 1; j < num_lines; j++) {
            if (array[i][j] > local_max) {
                local_max = array[i][j];
            }
        }
    }

    local_maxima[thread_num] = local_max;
    pthread_exit(NULL);
}
