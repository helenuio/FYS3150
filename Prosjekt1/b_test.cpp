#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// inline --> file scope
inline double f(double x){
  return 100.0*exp(-10.0*x);
}

int main(int argc, char* argv[]){ // argument count & argument vector
  int exponent; // 10^exponent, exponent = 3
  //string filename; // name of file taken from command line to read
  if( argc <= 1){
    cout << "Please write name (of file to read from as well as) the number of grid points n" << endl;
    exit(1); // terminate with error
  }
    else{
      //filename = argv[1]; // argv[0] is the name of the program
      exponent = atoi(argv[1]); // convert from string to integer
    }
    for (int i = 1; i <= exponent; i++){ // n=10, n=100, n=3 if exponent = 3
      int n = (int) pow(10.0,i);
      double h = 1.0/(n);
      double hh = h*h;

      double* x = new double[n+1];
      double* u = new double[n+1];
      double* g = new double[n+1];
      double* g_tilde = new double[n+1];
      double* b_tilde = new double[n+1];

      double* a = new double[n+1];
      double* b = new double[n+1];
      double* c = new double[n+1];

      u[0] = u[n] = 0.0; // boundary conditions
      for (int i = 0; i < n; i++){
        a[i] = -1;
        c[i] = -1;
        b[i] = 2;
        x[i] = i*h;
        g[i] = hh*f(i*h);
        cout << a[i] << endl;
      }

    delete [] x; delete [] b; delete [] a;
    delete [] c; delete [] u; delete [] g_tilde; delete [] b_tilde;
    }
return 0;
}
