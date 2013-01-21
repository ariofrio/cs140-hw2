/* CS 140
 * Assignment 1 : Matrix Vector Multiplication and the Power Method 
 * Group members : <Team-member-1> , <Team-member-2>
 * */

/* This file provides the placeholder function definitions, where you will be
 * implementing the assignment algorithms. You will be required to turn in 
 * only this file during the submission, where it will be compiled together
 * with our main function and tested. It is therefore required that you keep the 
 * function declaration formats unchanged.
 */

#include "powermethod.h"

#define debug(...) verbose && printf(__VA_ARGS__)
int verbose = 0;

// Subroutine for generating the input matrix
void generatematrix(double* mat, int size)
{
  int rank, nprocs;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  int nrows = size/nprocs;
  int localrow;
  for(localrow = 0; localrow < nrows; localrow++) {
    int globalrow = rank*nrows + localrow;
    int col;
    for(col=0; col<size; col++) {
      if(col <= globalrow) {
        mat[localrow*size + col] = globalrow + 1;
      } else {
        mat[localrow*size + col] = 0;
      }
    }
  }
  
  // Print the generated matrix only with argument -v.
  debug("%i: ", rank);
  int i;
  for(i = 0; i<nrows; i++) {
    debug("[");
    int j;
    for(j = 0; j<size; j++) {
      debug("%f, ", mat[i*size + j]);
    }
    debug("], ");
  }
  debug("\n");
}

// Subroutine to generate a random vector
void generatevec(double * x,int size)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0) {
    int i;
    for(i = 0; i < size; i++){
      x[i] = 1;
    }
  }
}

// Subroutine for the power method, to return the spectral radius
double powerMethod(double * mat, double * x, int size, int iter)
{
  return 1.618;
}
