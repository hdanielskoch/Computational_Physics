//LU Decomposition


#include <iostream>
#include "nr3.h"
#include "ludcmp.h"
using namespace std;


int main() {

  //Allocate a and b matrices
  MatDoub a(2,2);
  VecDoub b(2),x(2);

  a[0][0] = 0.789000;
  a[0][1] = 0.563010;
  a[1][0] = 1.182711;
  a[1][1] = 0.843952;

  b[0] = 0.225990;
  b[1] = 0.338759;
  
  //Create Upper and Lower matrix from A
  LUdcmp alu(a);

  //Solve the matrix for currents 
  alu.solve(b,x);

  cout << "x = "<< endl;
  cout << setprecision(15) << x[0] << endl;
  cout << setprecision(15) << x[1] << endl;

}
