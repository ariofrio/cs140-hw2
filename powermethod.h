#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>

// Function declarations
void generatematrix(double * mat, int size);
void generatevec(double * x, int size);
double powerMethod(double * mat, double * vec, int size, int iter);
