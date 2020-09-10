#include <iostream>
#include <new>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "lib.h"

using namespace std;

/* function declarations */

void inverse(double **, int);

void inverse(double **a, int n) // tar inn en matrise a med n
{
  int          i,j, *indx; // i, j integer og indx en vektor (peker på en vektor med int)
  double       d, *col, **y; // d er et tall, col er en vektor, y er en matrise

  // allocate space in memory
  indx = new int[n]; // indx skal peke på en vektor med n (integer) elementer
  col  = new double[n]; // col skal peke på en vektor med n (double) elementer
  y    = (double **) matrix(n, n, sizeof(double)); // y er en matrise med størrelse n*n

  ludcmp(a, n, indx, &d);   // LU decompose  a[][]

  printf("\n\nLU form of matrix of a[][]:\n");
  for(i = 0; i < n; i++) {
    printf("\n");
    for(j = 0; j < n; j++) {
      printf(" a[%2d][%2d] = %12.4E",i, j, a[i][j]);

  // find inverse of a[][] by columns
  for(j = 0; j < n; j++) {
    // initialize right-side of linear equations
    for(i = 0; i < n; i++) col[i] = 0.0;
    col[j] = 1.0;
    lubksb(a, n, indx, col);
    // save result in y[][]
    for(i = 0; i < n; i++) y[i][j] = col[i];
  }   //j-loop over columns
  // return the inverse matrix in a[][]
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++) a[i][j] = y[i][j];
  }

  free_matrix((void **) y);     // release local memory
  delete [] col;
  delete []indx;
} // End: function inverse()
