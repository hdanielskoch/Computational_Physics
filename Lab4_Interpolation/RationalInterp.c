//Rational Function Interpolation


#include <iostream>
#include "nr3.h"
#include "interp_1d.h"
using namespace std;


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
  Poly_interp data(x,data_small,size);
  

  //
  // Create output file
  //
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

  //Arbitrary interval to separate data by
  Doub interval = 0.001;

  //Interpolate to n_int equally spaced points
  for(Doub n_int= n_low; n_int < n_high; n_int += interval) {
    y=data.interp(n_int);
    err=data.dy;
    total_err = total_err + abs(err);
    if(abs(err) > worst_err) {
      worst_err = abs(err);
    }
    outfile << setw(12) << n_int << setw(10) << y << setw(10) << err << endl;
  }

  Doub avg_err = total_err / 200.0;
  cout << "Average error is: " << avg_err << endl;
  cout << "Worst error is: " << worst_err << endl;


  
}

int main() {
  Doub n = 5;
  polyInterp(n);

  n = 20;
  //polyInterp(n);
}


//Allocate and fill M data points with values for
//r and t over different values of n

/* struct Fill_Data { */
/*   int  M; */
/*   //Constructor */
/*   Fill_Data(Doub M_in) : M(M_in) { */
/*   cout << " constructing Fill_Data..." << endl; */
/*   } */
/*   //destructor */
/*   ~Fill_Data () { cout << " destructing Fill_Data..." << endl; } */
/*   //Set M data points */
/*   Doub set_M(Doub new_M) { return M = new_M; }; */

/*   //Set Coefficients (Calculated value for T_0) */
/*   Doub R_0 = 149600000000.0; */
/*   Doub T_0 = 3551170.0; */

/*   //Set range of n */
/*   Doub n_low = 0.0; //r=0 */
/*   Doub n_high = 3.14159265358979; //r=R_0 */

/*   //Create index i to convert n into indexes starting at 0 */
/*   Doub i = 0.0; */

/*   //Allocate size of vector (has to be an int) */
/*   int interval  = (n_high - n_low) / (M-1); */

/*   //Allocate vectors r and t */
/*   VecDoub r(int M), t(int M); */

  
/*   //Iterate over n and fill data */
/*   void fill() { */
/*     for(Doub n=n_low; n < n_high; n+= interval) { */
/*       r[i] = ((R_0) / 2.0) *(1.0 + cos(n));  */
/*       t[i] = ((T_0) / 2.0) *(n + sin(n)); */
/*       cout << t[i] << "     " << r[i] << endl; */
/*       i = i+ 1.0; */
/*     } */
/*   } */

/*   //Interpolate data */
/*   void poly_interpolation(VecDoub t(M), VecDoub r(M) { */
/*     //Interpolate */
/*     Poly_interp data(t,r,4); */
/*   } */

  
/* } */
