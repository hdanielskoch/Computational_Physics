//Imagine if the earth stopped its orbit around the sun. The earth
//would then start to move closer to the sun and eventually hit it.
//We can model the earth's movement by creating a function that is
//known parametrically with equations for the distance between the earth
//and sun (r)  which varies with a variable (n) as well as the time passed (t)
//which also varies with (n).


//This function creates two vectors (r) and (t) of size (M) where
//M is the number of data points requested by the user. The function
//interpolates between the two vectors. Next, it calculates the distance
//between the earth and sun in increments of 10 days until the eath hits
//the sun.

#include <iostream>
#include "nr3.h"
#include "interp_1d.h"
using namespace std;

void createData(int M) {
  Doub R_0 = 149600000000.0;
  Doub T_0 = 3551170.0;

  
  //Set range of n
  double n_low = 0.0; //r=0
  double n_high = 3.14; //r=R_0

  //Create index i to convert n into indexes starting at 0
  Doub i = 0.0;

  
  //Allocate vectors r and t
  VecDoub r(M), t(M);

  Doub interval  = (n_high - n_low) / (M - 1);

  //Iterate over n
  for(Doub n=n_low; n < n_high; n+= interval) {
    r[i] = ((R_0) / 2.0) *(1.0 + cos(n)); 
    t[i] = ((T_0) / 2.0) *(n + sin(n));
    i = i + 1.0;
  }

  //Interpolate
  Poly_interp data(t,r,4);


  //
  // Create output file
  //
  ofstream outfile;
  ostringstream filename;
  filename << "Radius vs time" << ends;
  outfile.open(filename.str().c_str());
  outfile.setf(ios::left);
  outfile << "#Radius (m)    " << "Time (days)   " << endl;

  
  //Test out value of x at 10 days
  Doub x=0.0;
  Doub y=0.0;
  Doub err=0.0;

  //define time at which earth hits sun
  Doub t_sun = 70.0;
  
  //Iterate over intervals of 10 days to find r
  for(int d=0; d< t_sun; d+=10) {
    x = d*24*60*60;
    y = data.interp(x);
    err=data.dy;

    outfile << setw(12) << d << setw(10) << y << endl;

    cout << "Radius after " << d << "  days is: " << y << " meters. " << endl;
  }
  
  //Add day 64
  Doub d=64.562095;
  x = d*24*60*60;
  y= data.interp(x);
  err=data.dy;
  cout << "Error of : "<< err/(60*24*24) << " days." << endl;
  outfile << setw(12) << d << setw(10) << y << endl;

  cout << "Radius after " << d << "  days is: " << y << " meters. " << endl;
}


int main() {
  //Set arbitrary number of points
  int M = 314;
  createData(M);
  
  
} 
