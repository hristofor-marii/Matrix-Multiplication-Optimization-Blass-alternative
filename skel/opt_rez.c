/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	double *A_mul, *B_mul, *B_mul_A, *res;

	A_mul = (double *) malloc (N * N *sizeof(double));
	B_mul = (double *) malloc (N * N * sizeof(double));
	B_mul_A = (double *) malloc (N * N * sizeof(double));
	res = (double *) malloc (N * N * sizeof(double));

	// imultim A-urile si B-urile
	for(int i = 0; i < N; i++)
	{
		register double *pA_origin = &A[i * N];
		register double *pBt_origin = &B[i];
		
		for(int j = 0; j < N; j++)
		{
			register double sum1 = 0.0;
			register double sum2 = 0.0;
			
			register double *pA = pA_origin;
			register double *pAt = &A[j * N];
			register double *pBt = pBt_origin;
			register double *pB = &B[j];
			register int i_mul = i * N + j;
			
			for(int k = 0; k < N; k++)
			{	
				
				sum1 += *pA * *pAt;
				pA++;
				pAt++;
				
				sum2 += *pBt * *pB;
			
				pBt += N;
				pB += N; 
			}
			A_mul[i_mul] = sum1;
			B_mul[i_mul] = sum2;
		}
	}

	// imultim B cu A_mul
	for(int i = 0; i < N; i ++)
	{
		register double *pB_origin = &B[i * N];

		for(int j = 0; j < N; j++)
		{

			register double sum1 = 0.0;

			register double *pA_mul = &A_mul[j];
			register double *pB = pB_origin;
			register int i_mul = i * N + j;

			for(int k = 0; k < N; k++)
			{

				sum1 += *pB * *pA_mul;
				
				pB++;
				pA_mul += N;
			}
			B_mul_A[i_mul] = sum1;
		}
	}

	free(A_mul);

	// suma finala
	for(int i = 0; i < N * N; i++)
	{
		 res[i] = B_mul_A[i] + B_mul[i];
	}
	
	free(B_mul_A);
	free(B_mul);

	return res;
	
}
