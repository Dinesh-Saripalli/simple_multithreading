#define WIN32_LEAN_AND_MEAN
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define NUM_THREADS 4
#define SIZE 10000000

int* arr;
double times[NUM_THREADS];

void* inc(void* arg)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int thread_ind = *((int*)arg);
    int start_idx = (thread_ind * SIZE) / NUM_THREADS;
    int end_idx = ((thread_ind + 1) * SIZE) / NUM_THREADS;

    // Get the current processor number
    DWORD_PTR currentProcessor = GetCurrentProcessorNumber();
    printf("Thread %d is running on processor %lu\n", thread_ind, currentProcessor);

    for (int i = start_idx; i < end_idx; i++) {
        arr[i] += 5;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = end.tv_sec - start.tv_sec;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    times[thread_ind] = elapsed;

    pthread_exit(NULL);
}

int main()
{
    arr = malloc(10000000 * sizeof(*arr));
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, inc, (void*)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        printf("Time taken for thread %d: %f seconds\n", i, times[i]);
    }

    return 0;
}
