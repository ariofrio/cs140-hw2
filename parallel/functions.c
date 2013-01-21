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

// Print the generated matrix only with argument -v.
void debug_matrix(double* mat, int nrows, int ncols) {
  int i;
  for(i = 0; i<nrows; i++) {
    debug("[");
    int j;
    for(j = 0; j<ncols; j++) {
      debug("%f, ", mat[i*ncols + j]);
    }
    debug("], ");
  }
  debug("\n");
}

void debug_vector(double* x, int size) {
  int i;
  for(i = 0; i<size; i++) {
    debug("%f, ", x[i]);
  }
  debug("\n");
}

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
  
  debug("%i: ", rank);
  debug_matrix(mat, nrows, size);
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

// Compute the norm (length) of vector x
double norm2(double* x, int size) {
  double sum = 0;
  int i;
  for(i = 0; i<size; i++) {
    sum += x[i] * x[i];
  }
  return sqrt(sum);
}

// Replace x by the matrix-vector product mat*x
double matVec(double* mat, double* x, int size) {
  int rank, nprocs;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  int nrows = size/nprocs;

  MPI_Bcast(
      x, size, MPI_DOUBLE,
      0, MPI_COMM_WORLD);

  double* y = (double *)malloc(nrows*sizeof(double));
  int localrow;
  for(localrow=0; localrow < nrows; localrow++) {
    int globalrow = rank*nrows + localrow;

    y[localrow] = 0;
    int j;
    for(j=0; j<size; j++) {
      y[localrow] += mat[localrow*size + j] * x[j];
    }
  }

  MPI_Gather(
      y, nrows, MPI_DOUBLE,
      x, nrows, MPI_DOUBLE,
      0, MPI_COMM_WORLD);
}

// Divide each element in vector x by a scalar
void divideVectorByScalar(double* x, int size, double scalar) {
  int i;
  for(i = 0; i < size; i++) {
    x[i] /= scalar;
  }
}

// Subroutine for the power method, to return the spectral radius
double powerMethod(double * mat, double * x, int size, int iter)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  int i;
  for(i = 0; i<iter; i++) {
    if(rank == 0) {
      debug("iteration %d: \n", i);
      double norm = norm2(x, size);
      debug("  norm = %f\n", norm);
      divideVectorByScalar(x, size, norm);
      debug("  x = "); debug_vector(x, size);
    }
    matVec(mat, x, size);
    //debug("mat = "); debug_matrix(mat, size);
  }
  if(rank == 0) {
    return norm2(x, size);
  } else {
    return 1234567;
  }
}

