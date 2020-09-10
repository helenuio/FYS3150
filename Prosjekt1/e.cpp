//  Simple matrix inversion example
#include <iostream>
#include <iomanip>
#include <new>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "lib.h"

using namespace std;

// f(x) -> right side of the equation
inline double f(double x)
{
  return 100.0*exp(-10.0*x);
}

/* function declarations */
void inverse(double **, double *, int);

void inverse(double **a, double *w, int n)
{
  int          i,j, *indx;
  double       d, *col, **y;
  // allocate space in memory
  indx = new int[n];
  col  = new double[n];
  y    = (double **) matrix(n, n, sizeof(double));

  ludcmp(a, n, indx, &d);   // LU decompose  a[][]
  printf("\n\nLU form of matrix of a[][]:\n");
  for(i = 0; i < n; i++) {
    printf("\n");
    for(j = 0; j < n; j++) {
      printf(" a[%2d][%2d] = %12.4E",i, j, a[i][j]);
    }
  }
  // find inverse of a[][] by columns
  for(j = 0; j < n; j++) {
    // initialize right-side of linear equations
    for(i = 0; i < n; i++) col[i] = 0.0;
    col[j] = 1.0;

    lubksb(a, n, indx, w);
    // save result in y[][]
    for(i = 0; i < n; i++) y[i][j] = col[i];
  }   //j-loop over columns
  // return the inverse matrix in a[][]
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) a[i][j] = y[i][j];
  }
  free_matrix((void **) y);     // release local memory
  delete [] col;
  delete []indx;
}  // End: function inverse()

int main(int argc, char* argv[])
{
  int exponent; // 10^exponent
  if( argc < 1)
  {
  cout << "Please write name of the number of grid points n" << endl;
  exit(1); // terminate with error
  }
  else
  {
    exponent = atoi(argv[1]); // convert from string to integer
  }

  clock_t start, finish; // declare start and final time
  start = clock();
  for (int i = 1; i <= exponent; i++) // n=10, n=100, n=3 if exponent = 3
  {
  int n = (int) pow(10.0,i);

  // set up the matrices with correct dimensions
  double** a = (double **) matrix(n, n, sizeof(double));
  double* w = new double[n]; // right hand side
  double* x = new double[n];
  double h = 1.0/(n);

  for(int i=0 ; i < n ; i++)
  {
  x[i] = i*h;
  double hh = h*h;
  w[i] = hh*f(x[i]);

        for(int j=0 ; j < n ; j++)
        {
           if (abs(i-j) > 1) {a[i][j] = 0.0;}
           if (i == j) {a[i][j] = 2.0;}
           else {a[i][j] = -1.0;}
        }
  }
  void inverse(double** a, double** w, int);

  finish = clock();
  double timeused = (double) (finish - start)/(CLOCKS_PER_SEC );
  cout << setw(5) << n;
  cout << setw(15) << timeused << endl;
  }
} // closing main function
