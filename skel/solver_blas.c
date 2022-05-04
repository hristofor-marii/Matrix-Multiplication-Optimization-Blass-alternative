/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"
/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	double *B_mul, *res; 

	B_mul = (double *) malloc (N * N * sizeof(double));
	res = (double *) malloc (N * N * sizeof(double));	
        
	// B_tr * B
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1, B, N, B, N, 0, B_mul, N);	

	// B = B * A superior
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, B, N);

	// B = B * A_tr
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, B, N);

	for(int i = 0; i < N * N; i++)
		res[i] = B[i] + B_mul[i];

	free(B_mul);

	return res;
}


