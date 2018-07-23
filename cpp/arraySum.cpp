#include <iostream>
#include <stdlib.h>
#include <omp.h>

using namespace std;

int n;
int* array;
int* thread_sums;

int main(int argc, char* argv[]) {
    
    //double wallTime1 = omp_get_wtime();

    if (argc < 2) {
        cerr << "Usage: ./program <Array Length> <Number Of Threads>" << endl;
        return -1;
    }

    n = atoi(argv[1]);
    array = new int[n];
    int thread_count = atoi(argv[2]);
    thread_sums = new int[thread_count];

    // Build the array
    for (int i = 1; i <= n; i++) {
        array[i-1] = i;
    }

    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank, num_thread;

        my_rank = omp_get_thread_num();
        num_thread = omp_get_num_threads();

        #pragma omp critical
        {
            thread_sums[my_rank] = 0;
            for (int r = my_rank; r < n; r += num_thread) {
                thread_sums[my_rank] += array[r];
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < thread_count; i++) {
        sum += thread_sums[i];
    }

    cout << "Expected Result: " << (n * (n+1)) / 2 << endl;
    cout << "Actual Result:   " << sum << endl;

    return 0;
}
