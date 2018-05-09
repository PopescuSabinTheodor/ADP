// MPI_RoyFloyd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define SIZE 5
#define INF 100
using namespace std;

int main(int argc, char* argv[])
{
	int numProc, rank;
	int matriceCost[SIZE][SIZE] = { { 0,4,INF,8,INF },
	{ 4,0,2,INF,INF },
	{ INF,2,0,1,3 },
	{ 8,INF,1,0,INF },
	{ INF,INF,3,INF,0 }
	};

	int matriceOptim[SIZE][SIZE];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);

	MPI_Bcast(matriceCost, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);


	for (int k = rank; k < SIZE; k++) {
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++) {
				if (matriceCost[i][k] + matriceCost[k][j] < matriceCost[i][j]) {

					matriceCost[i][j] = matriceCost[i][k] + matriceCost[k][j];

				}

			}

		}
	}

	MPI_Reduce(matriceCost, matriceOptim, SIZE*SIZE, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

	if (rank == 0) {


		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {

				matriceCost[i][j] = matriceOptim[i][j];

				printf("%d", matriceCost[i][j]);

				printf(" ");
			}

			printf("\n");
		}

	}
	MPI_Finalize();
	return 0;
}
