// MPI2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include <time.h>


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank;
	int numprocs;
	int number;
	int msg[2];
	int reply[2];

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	srand(time(NULL) + rank);
	number = rand() % 100;
	printf("nr: %d", number);
	msg[0] = number;
	msg[1] = rank;
	for (int i = 0; i < numprocs; i++) {
		if (rank == numprocs - 1)
			MPI_Send(&msg, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
		else
			MPI_Send(&msg, 2, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		if (rank == 0)
			MPI_Recv(&reply, 2, MPI_INT, numprocs - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		else
			MPI_Recv(&reply, 2, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if (msg[0] < reply[0])
		{
			msg[0] = reply[0];
			msg[1] = reply[1];
		}
	}
	printf("RANK:   %d,    Number:    %d", msg[1], msg[0]);
	
	MPI_Finalize();
	return 0;
}


