#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// object for output files
ofstream ofile;

// f(x) -> right side of the equation
inline double f(double x)
{
  return 100.0*exp(-10.0*x);
}

// exact solution
inline double exact(double x)
{
  return 1.0-(1-exp(-10))*x-exp(-10*x);
}

int main(int argc, char* argv[])
{ // argument count & argument vector
  int exponent; // 10^exponent, exponent = 3
  string filename; // name of file taken from command line to read
  if( argc <= 1)
  {
    cout << "Please write name of file to read from as well as the number of grid points n" << endl;
    exit(1); // terminate with error
  }
    else
    {
      filename = argv[1]; // argv[0] is the name of the program
      exponent = atoi(argv[2]); // convert from string to integer
    }
  for (int i = 1; i <= exponent; i++) // n=10, n=100, n=3 if exponent = 3
  {
      int n = (int) pow(10.0,i);
      double* x = new double[n+1];        x[0] = 0;
      double* u = new double[n+1];
      double* g = new double[n+1];        g[0] = 0;
      double* g_tilde = new double[n+1];  g_tilde[0] = 0;
      double* b_tilde = new double[n+1];  b_tilde[0] = 0;

      // elements along the matrix
      double* a = new double[n+1];          a[0] = a[n+1] = 0;
      double* b = new double[n+1];          b[0] = 0;
      double* c = new double[n+1];          c[0] = c[n+1] = 0;

      double h = 1.0/(n);
      double hh = h*h;

      for (int i = 1; i <= n+1; i++)
      {
        a[i] = c[i] = -1;
        b[i] = 2;
        x[i] = i*h;
        g[i] = hh*f(x[i]);
      }
    // new filename
    string fileout = filename;
    // convert exponent to string
    string exponent = to_string(i);
    // filename-i (where i = exponent)
    fileout.append(exponent);

    g_tilde[1] = g[1];
    b_tilde[1] = b[1];

    // forward substitution
    for (int i = 2; i <= n+1; i++)
    {
      b_tilde[i] = b[i] - (c[i-1]*a[i-1])/b_tilde[i-1];
      g_tilde[i] = g[i] - (g_tilde[i-1]*a[i-1])/b_tilde[i-1];
    }

    u[0] = u[n+1] = 0.0; // boundary conditions

    // backward substitution
    //u[n] = g_tilde[n]/b_tilde[n];
    for (int i = n; i >= 1; i--)
    {
      u[i] = (g_tilde[i]-(c[i]*u[i+1]))/b_tilde[i];
    }

    ofile.open(fileout);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    //      ofile << "       x:             approx:          exact:       relative error" << endl;
    for (int i = 1; i <= n; i++)
    {
      double xval = x[i];
      double RelativeError = fabs((exact(xval)-u[i])/exact(xval));
      ofile << setw(15) << setprecision(8) << xval;
      ofile << setw(15) << setprecision(8) << u[i];
      ofile << setw(15) << setprecision(8) << exact(xval);
      ofile << setw(15) << setprecision(8) << log10(RelativeError) << endl;
    }

    ofile.close();
    delete [] x; delete [] b; delete [] a;
    delete [] c; delete [] u; delete [] g_tilde; delete [] b_tilde;
  } // function looping over n=0,1,2

return 0;
} // main function
