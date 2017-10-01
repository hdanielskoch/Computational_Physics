//Evaluate the double integral for a function over
//the interior of an ellipse

#include <iostream>
#include "nr3.h"
#include "interp_1d.h"
#include "quadrature.h"
#include "romberg.h"

using namespace std;

//Functor for Inner Function
struct inner_X {
  
  //Initialize counter to count number of total integrations
  int counter;

  //Initialize y variable which is a constant in the inner integrand
  Doub y;

  //Constructor and destructor
  inner_X() { counter = 0;}
  ~inner_X() { cout << "counter: " << counter << endl; }

  //Changes the y constant in the inner integrand
  Doub setY(Doub y_in) {return y = y_in;};

  //Returns the integrand
  Doub operator()(Doub x) {
    counter++;
    return exp(-1.0 * x * cos(y));

  }

};

//Functor for outer integrand
struct outer_Y {

  //Initializes inner integrand
  inner_X funcX;

  //Initialize inner integral's limits of integration
  Doub xmax;
  Doub xmin;

  //constructor
  outer_Y() {;}
  //destructor
  ~outer_Y() { cout << "destructing outerY\n";}

  //This returns the inside integral at a specific y value
  Doub operator()(Doub y) {

    //Set the y value for the inner integral to the value being
    //used from the outer integral
    funcX.setY(y);

    //Set inner limits of integral
    xmax = 0.6 * y + 0.2 * sqrt(10.0 - 16.0 * y * y);
    xmin = 0.6 * y - 0.2 * sqrt(10.0 - 16.0 * y * y);

    //Return integrand at a specific y value
    return qromb(funcX, xmin, xmax);
  }
};


//Integrated Double Integral
int main() {
  
  //Set bounds of integral
  Doub tiny = 1.e-12;
  Doub y_min = -sqrt(5.0/8.0) + tiny;
  Doub y_max =  - y_min;

  //Initialize outer functor
  outer_Y funcY;

  //Integrate outer integral with y bounds
  Doub integral = qromb(funcY, y_min, y_max);

  //Print integral
  cout << "integral: " << setprecision(9) << integral << endl;

  return 0;
}
