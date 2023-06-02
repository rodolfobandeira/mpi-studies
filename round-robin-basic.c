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

    // Here we have a race condition. If the even ranks send first, then the odd ranks will block on the receive.
    if (rank % 2 == 0) {
        // Even ranks
        printf("%d: sending %ld to %d\n", rank, rand_mine, next);
        MPI_Send((void *)&rand_mine, 1, MPI_LONG, next, 1, MPI_COMM_WORLD);

        printf("%d: receiving from %d\n", rank, prev);
        MPI_Recv((void *)&rand_prev, 1, MPI_LONG, prev, 1, MPI_COMM_WORLD, &status);
    } else {
        // Odd ranks
        printf("%d: receiving from %d\n", rank, prev);
        MPI_Recv((void *)&rand_prev, 1, MPI_LONG, prev, 1, MPI_COMM_WORLD, &status);

        printf("%d: sending %ld to %d\n", rank, rand_mine, next);
        MPI_Send((void *)&rand_mine, 1, MPI_LONG, next, 1, MPI_COMM_WORLD);
    }
    
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
mpiexec -n 4 round-robin-basic  

3: hello (p=4) 
3: round robin: prev=2, next=0
3: random is: 45
3: receiving from 2
3: sending 45 to 0
3: >> I had 45, 2 had 45
3: goodbye
1: hello (p=4) 
1: round robin: prev=0, next=2
1: random is: 45
1: receiving from 0
1: sending 45 to 2
1: >> I had 45, 0 had 45
1: goodbye
0: hello (p=4)
0: round robin: prev=3, next=1
0: random is: 45
0: sending 45 to 1
0: receiving from 3
0: >> I had 45, 3 had 45
0: goodbye
2: hello (p=4)
2: round robin: prev=1, next=3
2: random is: 45
2: sending 45 to 3
2: receiving from 1
2: >> I had 45, 1 had 45
2: goodbye
*/