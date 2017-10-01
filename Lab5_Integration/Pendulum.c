//Integrate the period of a pendulum with a bob of mass m from
//an angle Theta_0 from the vertical

#include <iostream>
#include "nr3.h"
#include "quadrature.h"
#include "interp_1d.h"
#include "romberg.h"

using namespace std;

//Create Functor for integrand
struct Integrand {
  
  //Constructor allows user to change Theta_0
  Doub A;
  Integrand(Doub A_in) { A = A_in; }
  
  // destructor
  ~Integrand() { cout << "Destroying Integral..." << endl;}

  //Set Theta_0
  Doub set_Theta_0(Doub Theta_0) { return A = Theta_0; };
  
  //Returns the integrand
  Doub operator()(Doub theta) { return 1.0 / ( sqrt(cos(theta) -cos(A))); }
};


//Integrate function and create table of results for T/T_0 as
//a function of Theta_0

int main() {

  //Initialize limits
  Doub pi = acos(-1.0);
  Doub limit = pi; //Upper limit of Theta_Max
  Doub lower,upper;
  lower = 0.0; //Lower limit is 0
 
  //Create output file
  ofstream outfile;
  ostringstream filename;
  filename << "T_Ratio_vs_Theta_0" << ends;
  outfile.open(filename.str().c_str());
  outfile.setf(ios::left);
  outfile << "#Theta_0         T/T_0" << endl;

  //Initialize Integrand
  Integrand integrand(0);

  //Initialize the integrated value and T/T_0 for any Theta_0
  Doub Integ_Eval;
  Doub T_Ratio;

  //Loop over different Theta_0(s)
  for (Doub i=0.01; i<limit; i+=0.01) {
    integrand.set_Theta_0(i);

    //Set upper limit to current value of Theta_0
    upper = i;

    //Integrate from 0 to Theta_0
    Midsqu <Integrand> integrator(integrand,lower,upper);
    Integ_Eval = qromo(integrator);

    //Get T/T_0
    T_Ratio = answer * sqrt(2) / pi;
    outfile << setw(12) << i << setw(10) << T_Ratio << endl;
  }

}

