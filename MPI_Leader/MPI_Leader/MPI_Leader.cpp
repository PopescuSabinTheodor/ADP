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

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	
	
	if (rank == numprocs - 1) {
		srand(rank);
		int mynr = rand() % 100;
		int other;

		int leader;
		MPI_Send(&mynr, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Recv(&other, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("RANK :  %d    mynr:   %d    other:   %d", rank, mynr, other);
		if (mynr > other)
			leader = rank;
		else 
		{
			leader = rank - 1;
			mynr = other;
		}
		printf("Leader: %d", leader);
	}
	else
	{
		srand(rank);
		int mynr = rand() % 100;
		int other;
		int leader;
		MPI_Send(&mynr, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		if(rank==0)
			MPI_Recv(&other, 1, MPI_INT, numprocs - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		else
			MPI_Recv(&other, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("RANK :  %d    mynr:   %d    other:   %d", rank, mynr, other);
		if (mynr > other)
			leader = rank;
		else
		{
			leader = rank - 1;
			mynr = other;
		}
		printf("Leader: %d", leader);
	}
	
	MPI_Finalize();
	return 0;
}


