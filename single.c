#define WIN32_LEAN_AND_MEAN
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

int main()
{
    int* arr = malloc(10000000 * sizeof(*arr)); // Dynamically allocate array
    if (arr == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (int i = 0; i < 10000000; i++) {
        arr[i] = i + 1;
    }

    // start time
    clock_t start_time = clock();

    for (int i = 0; i < 10000000; i++) {
        arr[i] += 5;
    }
    DWORD_PTR currentProcessor = GetCurrentProcessorNumber();
    printf("Thread %d is running on processor %lu\n", 1, currentProcessor);

    // end time
    clock_t end_time = clock();

    // Calculate the time taken in seconds
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken to execute code is %f seconds\n", time_taken);

    free(arr); // Free the allocated memory
    return 0;
}
