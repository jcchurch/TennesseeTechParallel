#include <iostream>
#include "sys/time.h"
#include "omp.h"

using namespace std;

int main()
{
	const int NUM_THREADS = 1;
    const int SPACING = 20000;
    int* array = new int[NUM_THREADS*SPACING];

    for (int i = 0; i < NUM_THREADS; i++) {
        array[i*SPACING]=0;
    }

	struct timeval tv1, tv2;
	
	gettimeofday(&tv1,NULL); //get the current time
	
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		int index = omp_get_thread_num();
		for(int i = 0; i < 1e9; i++)
			array[index]++;
	}
		
	gettimeofday(&tv2,NULL);
	
	//this prints out the time in seconds between 
	//the two calls to gettimeofday
	cout << "Time: " << (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec) << endl;
	
	delete [] array;
	return 0;
}

