#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    // This is the data we want to transmit from rank 0 to rank 1
    // It's just an integer, but it could be a struct or an array
    // of integers, floats, doubles, etc.

    // "Rank" is the unique process ID. Goes from process 0 to process 1.
    int data = 42; 

    MPI_Init(&argc, &argv); // Initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes, which in this case will be 2

    // Think about a program that will run on all processes. So, we need to check if the rank is 0 or 1.
    // Where 0 is the origin (sending), and 1 is the destination (receiving).

    switch (rank) {
        case 0:
            // If the rank is 0, then we send the data to rank 1
            MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            // The first argument is the address of the data we want to send (in this case, an integer)
            // The second argument is the number of elements we want to send (in this case, just one integer)
            // The third argument is the type of data we want to send (in this case, an integer)
            // The fourth argument is the destination rank (in this case, rank 1)
            // The fifth argument is the tag (in this case, 0) - it's just an identifier for the message
            // The sixth argument is the communicator (in this case, MPI_COMM_WORLD)

            printf("Process %d sent data: %d\n", rank, data);
            break;
        case 1:
            // If the rank is 1, then we receive the data from rank 0
            MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // The first argument is the address of the data we want to receive (in this case, an integer)
            // The second argument is the number of elements we want to receive (in this case, just one integer)
            // The third argument is the type of data we want to receive (in this case, an integer)
            // The fourth argument is the source rank (in this case, rank 0) - it's just the sender
            // The fifth argument is the tag (in this case, 0) - it's just an identifier for the message
            // The sixth argument is the communicator (in this case, MPI_COMM_WORLD) - it's just a group of processes
            // The seventh argument is the status (in this case, MPI_STATUS_IGNORE) - it's just a flag to ignore the status

            printf("Process %d received data: %d\n", rank, data);
            break;
    }

    MPI_Finalize();

    return 0;
}