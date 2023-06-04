#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, number_of_procs;
    int sendbuf, recvbuf_sum, recvbuf_min, recvbuf_max, recvbuf_prod;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_procs); // Returns the size of the group associated with a communicator.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Determines the rank of the calling process in the communicator.

    sendbuf = 2;

    /*
        MPI_Allreduce is a function that performs an operation on the 
        data of all processes in a communicator and returns the result to all 
        processes.
        
        The fifth element of the function represents what it can be done:
        +-------------+---------------------------------------------------------+
        | Operator    | Description                                             |
        +-------------+---------------------------------------------------------+
        | MPI_MAX     | Returns the maximum element.                            |
        | MPI_MIN     | Returns the minimum element.                            |
        | MPI_SUM     | Sums the elements.                                      |
        | MPI_PROD    | Multiplies the elements.                                |
        | MPI_LAND    | Performs a logical AND across the input elements.       |
        | MPI_BAND    | Performs a bitwise AND across the input elements.       |
        | MPI_LOR     | Performs a logical OR across the input elements.        |
        | MPI_BOR     | Performs a bitwise OR across the input elements.        |
        | MPI_LXOR    | Performs a logical exclusive OR across the input elem.  |
        | MPI_BXOR    | Performs a bitwise exclusive OR across the input elem.  |
        | MPI_MAXLOC  | Returns the maximum value and the rank that owns it.    |
        | MPI_MINLOC  | Returns the minimum value and the rank that owns it.    |
        +-------------+---------------------------------------------------------+
    */
    MPI_Allreduce(&sendbuf, &recvbuf_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&sendbuf, &recvbuf_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&sendbuf, &recvbuf_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&sendbuf, &recvbuf_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);


    if (rank == 0) {
        printf("MPI_SUM for all processes (%d * %d) = %d \n", sendbuf, number_of_procs, recvbuf_sum);
        printf("MPI_MIN for all processes: %d \n", recvbuf_min);
        printf("MPI_MAX for all processes: %d \n", recvbuf_max);
        printf("MPI_PROD for all processes: %d \n", recvbuf_prod);
    }

    /*
    Windows: mpiexec -n 3 mpi-allreduce.exe
    Linux: mpirun -np 3 ./mpi-allreduce.x

    MPI_SUM for all processes (2 * 3) = 6 
    MPI_MIN for all processes: 2
    MPI_MAX for all processes: 2
    MPI_PROD for all processes: 8
    */

    MPI_Finalize();

    return 0;
}
