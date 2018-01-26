/*
 * File:        cachelab.c
 * Description: Cache Lab helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "cachelab.h"

shift_funct_t func_list[MAX_SHIFT_FUNCS];
int func_counter = 0;

/*
 * printSummary - Summarize the cache simulation statistics. Student cache
 *                simulators must call this function in order to be properly
 *                autograded.
 */
void printSummary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
    FILE* output_fp = fopen(".csim_results", "w");
    assert(output_fp);
    fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
    fclose(output_fp);
}

/*
 * initMatrix - Initialize the given matrix with random values [0, 999].
 */
void initMatrix(int M, int N, int A[M][N])
{
    int i, j;
    srand(time(NULL));
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            A[i][j] = rand()%1000;
        }
    }
}

/*
 * randMatrix - Generates a random matrix with the specified dimensions.
 */
void randMatrix(int M, int N, int A[N][M])
{
    int i, j;
    srand(time(NULL));
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            A[i][j] = rand();
        }
    }
}

/*
 * correctShift - Baseline matrix shift function used to evaluate correctness.
 */
void correctShift(int M, int N, int A[M][N], int s, int E, int b)
{
    int i, j,temp;
    for (i = 1; i < M; i++){
        for (j = 0; j < N; j++){
            temp = A[i][j];
            A[i][j] = A[i-1][j];
            A[i-1][j] = temp;
        }
    }
}

/*
 * registerShiftFunction - Add the given shift function into your list of
 *                         functions to be tested.
 */
void registerShiftFunction(void (*shift)(int M, int N, int[M][N], int s, int E, int b),
                           char* desc)
{
    func_list[func_counter].func_ptr = shift;
    func_list[func_counter].description = desc;
    func_list[func_counter].correct = 0;
    func_list[func_counter].num_hits = 0;
    func_list[func_counter].num_misses = 0;
    func_list[func_counter].num_evictions =0;
    func_counter++;
}
