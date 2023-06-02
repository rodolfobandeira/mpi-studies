#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int send_data, recv_data, source_rank, dest_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
    The MPI_Sendrecv function is useful in situations where two processes need 
    to exchange data with each other simultaneously. It combines the functionality 
    of sending and receiving into a single function call, ensuring synchronized 
    communication between two processes.

    As we can see in the function's syntax, it combines MPI_Send with MPI_Recv into
    a single function call. The function takes the following arguments:

    int MPI_Sendrecv(
        const void* sendbuf,
        int sendcount,
        MPI_Datatype sendtype,
        int dest,
        int sendtag,
        void* recvbuf,
        int recvcount,
        MPI_Datatype recvtype,
        int source,
        int recvtag,
        MPI_Comm comm,
        MPI_Status* status
    );

    */

   switch (rank) {
       case 0:
            send_data = 2023;
            dest_rank = 1; // Sends data to process 1
            source_rank = 1; // Receives data from process 1

            MPI_Sendrecv(&send_data, 1, MPI_INT, dest_rank, 0, &recv_data, 1, MPI_INT, source_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d sent %d and received %d\n", rank, send_data, recv_data);
            break;
       case 1:
            send_data = 2014;
            dest_rank = 0; // Sends this data to process 0
            source_rank = 0; // Receives data from process 0

            MPI_Sendrecv(&send_data, 1, MPI_INT, dest_rank, 0, &recv_data, 1, MPI_INT, source_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d sent %d and received %d\n", rank, send_data, recv_data);
            break;
   }

    MPI_Finalize();

    /*
    rodolfo @ laptop ~/src/github.com/rodolfobandeira/mpi-studies (main)
    └─ $ ▶ mpicc sendrecv.c -o sendrecv.x
    
    rodolfo @ laptop ~/src/github.com/rodolfobandeira/mpi-studies (main)
    └─ $ ▶ mpirun -np 4 ./sendrecv.x 
        Process 0 sent 2023 and received 2014
        Process 1 sent 2014 and received 2023
    */

    return 0;
}
