#include <iostream>
#include <cstdlib>
#include <time.h>
#include <omp.h>

using namespace std;

char* grid;
char* temp_grid;
int rows;
int cols;
int gens;

void init_grid();
void do_iteration(int);
char get_value(int, int);
int get_index(int, int);
void print_grid();

void writeToTempGrid(int, int);

int main(int argc, char *argv[]) {

    if(argc != 5) {
        cout << "usage: rows cols generations threads\n";
        exit(0);
    }

    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    gens = atoi(argv[3]);
    int thread_count = atoi(argv[4]);
    
    grid = new char[rows*cols];
    temp_grid = new char[rows*cols];
    
    init_grid();
    print_grid();

    for(int i = 0; i < gens; i++)
    {
        do_iteration(thread_count);
        print_grid();
    }
    
    return 0;
}

void init_grid()
{
    srand(time(NULL));
    for(int i = 0; i < rows*cols; i++)
        grid[i]=rand()%2;
}

void writeToTempGrid(int r, int c) {
    int liveNeighbors = 
                    get_value(r - 1, c - 1) + 
                    get_value(r - 1, c    ) + 
                    get_value(r - 1, c + 1) + 
                    get_value(r    , c - 1) + 
                    get_value(r    , c + 1) + 
                    get_value(r + 1, c - 1) + 
                    get_value(r + 1, c    ) + 
                    get_value(r + 1, c + 1) ;
    if (liveNeighbors < 2 || liveNeighbors > 3)
        temp_grid[get_index(r, c)] = 0;
    if (liveNeighbors == 3)
        temp_grid[get_index(r, c)] = 1;
    if (liveNeighbors == 2)
        temp_grid[get_index(r, c)] = get_value(r, c);
}

void do_iteration(int thread_count)
{

    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank, num_thread;
        
        my_rank = omp_get_thread_num();
        num_thread = omp_get_num_threads();
        
        #pragma omp critical
        {
             for (int r = my_rank; r < rows; r += num_thread)
                for (int c = 0; c < cols; c++)
                {
                    writeToTempGrid(r, c);
                }
        }
    }

    char* swap = temp_grid;
    temp_grid = grid;
    grid = swap;
}

char get_value(int row, int col)
{
    return grid[get_index(row, col)];
}

int get_index(int row, int col)
{
    return ((row + rows) % rows) * cols + ((col + cols) % cols);
}

void print_grid()
{
    cout << endl;
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c <  cols; c++)
        {
            cout << (get_value(r, c)?'1':'0') << " ";
        }
        cout << endl;
    }
}

