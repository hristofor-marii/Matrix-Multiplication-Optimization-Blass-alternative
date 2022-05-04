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

	double *firstPh, *B_mul, *B_mul_A;

	firstPh = (double *) malloc (N * N *sizeof(double));
	B_mul = (double *) malloc (N * N * sizeof(double));
	B_mul_A = (double *) malloc (N * N * sizeof(double));
	
	// imultim B cu A superior
	for(int i = 0; i < N; i++)
	{
		register double *pB_origin = &B[i * N];
		
		for(int j = 0; j < N; j++)
		{
			register double sum1 = 0.0;
			
			register double *pB = pB_origin;
			register double *pA = &A[j];

			register int i_mul = i * N + j;
			
			// k < j + 1 deoarece A superior triunghiulara
			// B[0] * A[0] dupa B[0,1] * A[1,4] ...
			for(int k = 0; k < j + 1; k++)
			{	
				
				sum1 += *pB * *pA;
				pB++;
				pA += N;
				
			}

			B_mul_A[i_mul] = sum1;
		}
	}

	// B_mul_A * A_tr => linie cu linie deoarece nu construim 
	// explicit A_tr facem operatiile pe A => liniile lui A
	for(int i = 0; i < N; i++)
	{
		register double *pB_mul_A_origin = &B_mul_A[i * N];

		for(int j = 0; j < N; j++)
		{
			register double sum1 = 0.0;
			register double *pB_mul_A = pB_mul_A_origin + j;
			register double *pA_tr = &A[j * N + j];
			register int i_mul = i * N + j;

			// Deoarece A superior triunghiulare iar noi
			// mergem pe liniile lui A =>
			// B_mul_A[0,1,2] * A[0,1,2] dupa
			// B_mul_A[1,2] * A[4,5], A[3] = 0 deci il evit
			// adunand j la pointerii catre inceput iar
			// k il limitez la N -j iteratii necesare
			for(int k = 0; k < N - j; k ++)
			{
				sum1 += *pB_mul_A * *pA_tr;
				pB_mul_A++;
				pA_tr++;
			}

			firstPh[i_mul] = sum1;

		}
	}

	free(B_mul_A);

	// imultim B_tr cu B
	for(int i = 0; i < N; i ++)
	{
		register double *pBt_origin = &B[i];

		for(int j = 0; j < N; j++)
		{

			register double sum1 = 0.0;

			register double *pBt = pBt_origin;
			register double *pB = &B[j];

			register int i_mul = i * N + j;

			for(int k = 0; k < N; k++)
			{

				sum1 += *pBt * *pB;
			
				pBt += N;
				pB += N; 
			}
			
			B_mul[i_mul] = sum1;
		}

	}

	// suma finala
	for(int i = 0; i < N * N; i++)
	{
		  firstPh[i] += B_mul[i];
	}
	
	free(B_mul);

	return firstPh;
	
}
