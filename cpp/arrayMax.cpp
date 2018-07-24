#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

int n;
int* array;
int* thread_maxs;

int main(int argc, char* argv[]) {

    double wallTime1 = omp_get_wtime();
    
    srand(time(0));
    
    if (argc < 2) {
        cerr << "Usage: ./program <Array Length> <Number Of Threads>" << endl;
        return -1;
    }

    n = atoi(argv[1]);
    array = new int[n];
    int thread_count = atoi(argv[2]);
    thread_maxs = new int[thread_count];

    // Build the array
    int trueMax = -1;
    for (int i = 1; i <= n; i++) {
        array[i-1] = rand();
        if (array[i-1] > trueMax) {
            trueMax = array[i-1];
        }
    }

    double wallTime2 = omp_get_wtime();

    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank, num_thread;

        my_rank = omp_get_thread_num();
        num_thread = omp_get_num_threads();

        #pragma omp critical
        {
            thread_maxs[my_rank] = array[my_rank];
            int start = my_rank + num_thread;
            for (int r = start; r < n; r += num_thread) {
                if (array[r] > thread_maxs[my_rank]) {
                    thread_maxs[my_rank] = array[r];
                }
            }
        }
    }

    int max = thread_maxs[0];
    for (int i = 1; i < thread_count; i++) {
        if (thread_maxs[i] > max) {
            max = thread_maxs[i];
        }
    }

    double wallTime3 = omp_get_wtime();

    cout << "Expected Result: " << trueMax << " ( " << (wallTime2 - wallTime1) << " seconds ) " << endl;
    cout << "Actual Result:   " << max     << " ( " << (wallTime3 - wallTime2) << " seconds ) " << endl;

    return 0;
}
