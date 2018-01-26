/*
 * File:        cachelab.h
 * Description: Prototypes for Cache Lab helper functions defined in cachelab.c
 */

#ifndef CACHELAB_TOOLS_H
#define CACHELAB_TOOLS_H

#define MAX_SHIFT_FUNCS 100

typedef struct shift_funct {
  void (*func_ptr)(int M,int N,int[M][N], int s, int E, int b);
  char* description;
  char correct;
  unsigned int num_hits;
  unsigned int num_misses;
  unsigned int num_evictions;
} shift_funct_t;

/* Prints final hit and miss statistics */
void printSummary(int hits,  /* number of  hits */
				  int misses, /* number of misses */
				  int evictions); /* number of evictions */

/* Fill the matrix with data */
void initMatrix(int M, int N, int A[M][N]);

/* The baseline shift function that produces correct results. */
void correctShift(int M, int N, int A[M][N], int s, int E, int b);

/* Add the given function to the function list */
void registerShiftFunction(
    void (*shift)(int M,int N,int[M][N], int s, int E, int b), char* desc);

#endif /* CACHELAB_TOOLS_H */
