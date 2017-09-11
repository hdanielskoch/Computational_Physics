#include <iostream>
#include "nr3.h"
#include "interp_1d.h"
#include "polcoef.h"
using namespace std;

//polyInterp takes in the number of data points (size) to be evaluated by the
//function f(x)=e^(-x^2)/(1+25X^2). It allocates two vectors of size (size)
//and interpolates at many values on the interval [-1,1]. It also determines the//coefficients of the interpolating polynomial as well as the error.

void polyInterp(Doub size) {
  //Set range of n
  double n_low = -1.0; 
  double n_high = 1.0; 

  //Create index i to convert n into indexes starting at 0
  Doub i;
  
  //Allocate vector data_small 
  VecDoub data_small(size);
  VecDoub x(size);

  //Set interval of spacing between data points
  Doub interval = (n_high - n_low) / (size - 1);

  //Iterate over n to fill data_small and x
  for(double n=n_low; n <= n_high; n+= interval) {
    data_small[i] = exp(-n*n) / (1+ 25*(n*n));
    x[i] = n;
    i = i+1; //Go to next index in vector
  }
  cout << endl;
  
  //Interpolate
  Rat_interp data(x,data_small,size);
  
  // Create output file
  ofstream outfile;
  ostringstream filename;
  filename << "f(x) vs N_int_for_N=" << size << ends;
  outfile.open(filename.str().c_str());
  outfile.setf(ios::left);
  outfile << "#f(x)       " << "N_int" << endl;
  
  //Initialize interpolation values
  Doub y=0.0;
  Doub err=0.0;
  Doub total_err=0.0;
  Doub worst_err=0.0;

  //Create arbitrary interval to separate data
  Doub interv = 0.01;

  //Interpolate to n_int equally spaced points
  for(Doub n_int= n_low; n_int < n_high; n_int += interv) {
    y=data.interp(n_int);
    err=data.dy;
    total_err = total_err + abs(err);
    if(abs(err) > worst_err) {
      worst_err = abs(err);
    }
    outfile << setw(12) << n_int << setw(10) << y << setw(10) << err << endl;
  }

  //Calculate total error and average error
  Doub total_points = (n_high - n_low) / interv;
  Doub avg_err = total_err / total_points;
  cout << "Average error is: " << avg_err << endl;
  cout << "Worst error is: " << worst_err << endl;

  //Initiate Coef matrix using polcof
  VecDoub cof(size);
  polcof(x,data_small,cof);

  //Print coefficients
  cout << "Using polcof..." << endl;
  for(int c=0; c<size; c++) {
    cout << "c_" << c << " = " << cof[c] << endl;
  }

  //Initiate Coef matrix using polcoe
  VecDoub coe(size);
  polcoe(x,data_small,coe);

  //Print coefficients
  cout << endl << "Using polcoe..." << endl;
  for(int c=0; c<size; c++) {
    cout << "c_" << c << " = " << coe[c] << endl;
  }
  
}

int main() {
  //Interpolate from 5 data points
  Doub n = 5;
  // polyInterp(n);

  //Interpolate from 20 data points
  n = 20.0;
  polyInterp(n);
}
