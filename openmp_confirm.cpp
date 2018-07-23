#include <cstdio>
#include "omp.h"

int main() 
{
		#pragma omp parallel num_threads(2)
		{
			#pragma omp critical
			printf("hi from thread %d\n", omp_get_thread_num());
		}
		return 0;
}