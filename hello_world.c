#include <stdio.h>
#include <mpi.h>

/*
In parallel programming with MPI (Message Passing Interface) and the C language, 
the term "rank" refers to the unique identifier assigned to each process 
in a parallel program.

MPI allows you to create a group of processes that can communicate and 
coordinate with each other by passing messages. Each process in the program 
is assigned a rank, which serves as its identifier within the group.

The rank values are integers ranging from 0 to the total number of processes 
minus one. The rank 0 is typically used to denote the master process or the 
process with special responsibilities, such as coordinating the computation, 
gathering results, or distributing tasks to other processes.

The rank provides a way for each process to distinguish itself from others 
and enables selective communication between specific processes. For example, 
if you want process A to send a message to process B, you need to specify 
the ranks of both A and B in the MPI communication function.
*/

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank (unique identifier) of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the total number of processes

    printf("Hello from process %d of %d\n", rank, size);

    MPI_Finalize();

    return 0;
}
