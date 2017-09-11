//Flight time of a projectile in the presence of a retarding force

#include <iostream>
#include "nr3.h"
#include "roots.h"
using namespace std;


struct  Flight_Time {
  double k; 
  
  // constructor
  Flight_Time(double k_in) { k = k_in; }
  // destructor
  ~Flight_Time() { }
  // set coefficient
  double set_coefficient(double coef) { return k = coef; };

  //
  //Operator returns the function for flight time with T subtracted from it.
  //This can be used to find the roots of the function to get T values.
  //
  double operator()(double T_n) { return (3.531194 + (1/k))*(1-(exp((-k)*T_n))) - T_n; }
};

//
// define functor evaluator
//
template <class T> double functor_evaluator(T & func, double T_n) {
  return func(T_n);
};

int main() {
  //
  //Define rootfinding parameters
  //Found brackets by graphing the function on a calculator
  //
  Doub a = 1;
  Doub b = 10;
  Doub tol = 0.001;
  
  //
  // Create output file
  //
  ofstream outfile;
  ostringstream filename;
  filename << "k vs T" << ends;
  outfile.open(filename.str().c_str());
  outfile.setf(ios::left);
  outfile << "#k       " << "T (roots of function)" << endl;

  
  //
  //Iterate over all k's from 0 0.5 seconds
  //
  for (double k=0.001; k<0.5; k+=0.005) {
      //
      //Create instance of flight time
      //
      Flight_Time flight(k);

      //
      //Find Root of function (Root=T)
      //
      Doub root = zbrent(flight, a, b, tol);
      //
      //Write to output file
      //
      outfile << setw(12) << k  << setw(15) << root  << endl;

      cout << k << "       " << root  << endl;
  }
  outfile.close();
}  
