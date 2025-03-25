#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    long long start;
    long long end;
    long long partial_sum;
} ThreadData;

// Thread fuction to compute partial sum
void *partial_sum_func(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    data->partial_sum = 0;
    for (long long i = data->start; i <= data->end; i++)
    {
        data->partial_sum += i;
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // exception handling if input format is wrong
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s numThreads n\n", argv[0]);
        return 1;
    }
    // intialize variables
    int numThreads = atoi(argv[1]);
    long long n = atoll(argv[2]);
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    // Create threads (if n%numThreads != 0, the first remainder threads will have 1 more element)
    long long chunk = n / numThreads;
    long long remainder = n % numThreads;

    // Assign start and end values to each thread
    long long current_start = 1;
    for (int i = 0; i < numThreads; i++)
    {
        threadData[i].start = current_start;
        long long extra = (i < remainder) ? 1 : 0;
        threadData[i].end = current_start + chunk - 1 + extra;
        current_start = threadData[i].end + 1;

        // Create thread
        if (pthread_create(&threads[i], NULL, partial_sum_func, (void *)&threadData[i]) != 0)
        {
            perror("pthread_create failed");
            exit(1);
        }
    }

    // Wait for threads to finish and accumulate partial sums
    long long total_sum = 0;
    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
        total_sum += threadData[i].partial_sum;
    }

    printf("Sum of numbers from 1 to %lld is: %lld\n", n, total_sum);
    return 0;
}
