/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	
	double *firstPh, *B_tr, *A_tr, *B_mul, *B_mul_A;

	firstPh = (double *) calloc (N * N, sizeof(double));
	B_tr = (double *) calloc (N * N, sizeof(double));
	B_mul = (double *) calloc (N * N, sizeof(double));
	B_mul_A = (double *) calloc (N * N, sizeof(double));
	A_tr = (double *) calloc (N * N, sizeof(double));
	
	// construin A_tr si B_tr
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int i_mt = i * N + j;
			int i_tr = j * N + i;
			
			A_tr[i_tr] = A[i_mt];
			B_tr[i_tr] = B[i_mt];
		}
	}
	
	// inmultesc B cu A superior
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int i_mul = i * N + j;
			
			// j + 1 pentru a elimina inmultirea cu 0
			for(int k = 0; k < j + 1; k++) 
			{
				int i_left = i * N + k;
				int i_right = k * N + j;
				B_mul_A[i_mul] += B[i_left] * A[i_right];
			}
		}
	}


	// B_mul_A * A_tr
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int i_mul = i * N + j;
			
			// k + j < N pentru a corespunde operatiilor
			// necesare (k + j) de la i_left i_right
			// care va ajuta in eliminarea inmultirii cu 0
			for(int k = 0; k + j < N; k++)
			{
				int i_left = i * N + (k + j);
				int i_right = (k + j) * N + j;
				
				firstPh[i_mul] += B_mul_A[i_left] * A_tr[i_right];			
				
			}
		}
	}
	
	free(B_mul_A);
	free(A_tr);
	
	// B_tr * B
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int i_mul = i * N + j;
			
			for(int k = 0; k < N; k++)
			{
				int i_left = i * N + k;
				int i_right = k * N + j;

				B_mul[i_mul] += B_tr[i_left] * B[i_right];

			}
		}
	}

	free(B_tr);

	
	// suma finala
	for(int i = 0; i < N * N; i++)
	{
		 firstPh[i] += B_mul[i];
	}

	free(B_mul);

	return firstPh;
}

