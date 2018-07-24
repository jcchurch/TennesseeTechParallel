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

    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int r = 0; r < n; r++) {
        sum += array[r];
    }

    cout << "Expected Result: " << (n * (n+1)) / 2 << endl;
    cout << "Actual Result:   " << sum << endl;

    return 0;
}
