/*
 * File: shift.c
 *
 * Each matrix shift function must have a prototype of the form:
 * void matrix_shift(int M, int N, int A[M][N], int s, int E, int b);
 *
 */
#include <stdio.h>
#include <string.h>
#include "cachelab.h"

/*
 * matrix_shift_submit - This is the solution matrix shift function that you
 *     will be graded on for Part B of the lab submissions. Do not change
 *     the description string "Matrix shift submission", as the driver
 *     searches for that string to identify the matrix shift function to
 *     be graded.
 */
char matrix_shift_submit_desc[] = "Matrix shift submission";
void matrix_shift_submit(int M, int N, int A[M][N], int s, int E, int b)
{
    int i, j, temp1, temp2;
    for (j=0;j<N;j+=2){
        for (i=1;i<M;i++){ /*go by columns*/
            temp1 = A[i-1][j]; /*save 2 row items*/
            temp2 = A[i-1][j+1]; /*save 2 row items*/
            A[i-1][j] = A[i][j]; /*copy it over*/
            A[i-1][j+1] = A[i][j+1]; /*copy it over*/
            A[i][j] = temp1;
            A[i][j+1] = temp2;
        }
    }

/*this is left over from an attempt to optimize earlier, mean to show that 2 temps is kind of the
  limit for improving performance this way.*/
/* 
int i, j, temp1, temp2, temp3, temp4;
    for (j=0;j<N;j+=4){
        for (i=1;i<M;i++){
            temp1 = A[i-1][j];
            temp2 = A[i-1][j+1];
            temp3 = A[i-1][j+2];
            temp4 = A[i-1][j+3];
            A[i-1][j] = A[i][j];
            A[i-1][j+1] = A[i][j+1];
            A[i-1][j+2] = A[i][j+2];
            A[i-1][j+3] = A[i][j+3];
            A[i][j] = temp1;
            A[i][j+1] = temp2;
            A[i][j+2] = temp3;
            A[i][j+3] = temp4;
        }
    }*/
}

/*
 * You can define additional matrix shift functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * matrix_shift - A simple matrix shift function, not optimized for the cache.
 */
char matrix_shift_function_desc1[] = "Matrix shift function 1";
void matrix_shift_function1(int M, int N, int A[M][N], int s, int E, int b)
{
    int i, j, temp;
    for (i = 1; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            temp = A[i][j];
            A[i][j] = A[i-1][j];
            A[i-1][j] = temp;
        }
    }
}

/*
 * registerFunctions - This function registers your matrix shift
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     matrix shift strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerShiftFunction(matrix_shift_submit, matrix_shift_submit_desc);

    /* Register any additional matrix shift functions */
    registerShiftFunction(matrix_shift_function1, matrix_shift_function_desc1);
}
