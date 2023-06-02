#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


void round_robin(int rank, int num_procs) {
    long int rand_mine, rand_prev;
    int next = (rank + 1) % num_procs;
    int prev = (rank + num_procs - 1) % num_procs;
    MPI_Status status;

    srand(time(NULL) + rank);
    rand_mine = rand() / (RAND_MAX / 100);
    
    printf("%d: round robin: prev=%d, next=%d\n", rank, prev, next);
    printf("%d: random is: %ld\n", rank, rand_mine);

    MPI_Sendrecv((void *)&rand_mine, 1, MPI_LONG, next, 1, (void *)&rand_prev, 1, MPI_LONG, prev, 1, MPI_COMM_WORLD, &status);
    
    printf("%d: >> I had %ld, %d had %ld\n", rank, rand_mine, prev, rand_prev);
}

int main(int argc, char** argv) {
    int rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 

    printf("%d: hello (p=%d) \n", rank, num_procs);
    round_robin(rank, num_procs);
    printf("%d: goodbye\n", rank);

    MPI_Finalize();

    return 0;
}


/*
Windows
mpiexec -n 3 round-robin-basic2

1: hello (p=3) 
1: round robin: prev=0, next=2
1: random is: 69
1: >> I had 69, 0 had 69
1: goodbye
0: hello (p=3) 
0: round robin: prev=2, next=1
0: random is: 69
0: >> I had 69, 2 had 69
0: goodbye
2: hello (p=3)
2: round robin: prev=1, next=0
2: random is: 69
2: >> I had 69, 1 had 69
2: goodbye
*/