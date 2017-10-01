#include <iostream>
#include "nr3.h"
#include "quadrature.h"
#include "interp_1d.h"
#include "romberg.h"

using namespace std;

//
// define functors
//

struct Integrand {
  //destructor
  ~Integrand() { cout << "Destroying Integral..." << endl;}

  //here's where the function is:
  double operator()(Doub y) {
      Doub exponent_1 = -sin(y) * (0.6*y + 1.0/5.0 * sqrt(10.0-16.0*y*y));
      Doub exponent_2 = -sin(y) * (0.6*y - 1.0/5.0 * sqrt(10.0-16.0*y*y));
      return  -1.0/sin(y) * (exp(exponent_1) - exp(exponent_2)); }
};


//
// define functor evaluator
//
template <class T> double functor_evaluator(T & func, double x) {
  return func(x);
};


int main() {
  Doub x = sqrt(5.0/8.0);

  Integrand integrand_1;
  Integrand integrand_2;

  //Why do we need this?
  Midpnt <Integrand> first_int(integrand_1,-x,0);
  Midpnt <Integrand> second_int(integrand_2,0,x);

  //Integrate

  Doub total = qromo(first_int) + qromo(second_int);
  cout << setprecision(9) << total << endl;

  
  
}

