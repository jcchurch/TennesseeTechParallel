#include <iostream>
#include <stdlib.h>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {
    
    //double wallTime1 = omp_get_wtime();

    if (argc < 2) {
        cerr << "Usage: ./program <Number Of Threads>" << endl;
        return -1;
    }

    int thread_count = atoi(argv[1]);

    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank, num_thread;

        my_rank = omp_get_thread_num();
        num_thread = omp_get_num_threads();

        #pragma omp critical
        {
            if (my_rank == 0) {
                cout << "No of thread spawn: " << num_thread << endl;
            }

            cout << "Hello from " << my_rank << " of " << num_thread << endl;
        }
    }

    return 0;
}
