// MPI2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	if (rank == 0)
	{
		int section = 0;
		for (int i = 0; i < 4; i++)
		{
			section = (i+1) * (100 / 4);
			if(i<3)
			MPI_Send(&section, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
		}
		for (int i = 2; i < 100/4; i++)
		{
			bool ok = true;
			for (int d = 2; d < i / 2; d++)
			{
				if (i%d == 0) {
					ok = false;
					break;
				}
			}
			if (ok == true)
				printf("%d ", i);
		}
	}
	else
	{
		int section;
		MPI_Recv(&section, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int x = rank;
		for (int i = section; i < section+25; i++)
		{
			bool ok = true;
			for (int d = 2; d < i / 2; d++)
			{
				if (i%d == 0) {
					ok = false;
					break;
				}
			}
			if (ok == true)
				printf("%d ", i);
		}
	}
	MPI_Finalize();
    return 0;
}

