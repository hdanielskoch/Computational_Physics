//Single Slit Experiment
//Route Finding Methods
//Use roout-finding method to locate maxima of first five
//side peaks and evaluate intensities of their maxima

#include <iostream>
#include "nr3.h"
#include "roots.h"
using namespace std;


//
// define Intensity function for single slit interference
//
double intensity(double x) {
  double  result = (sin(x)/x) * (sin(x)/x);
  return result;
}


//
// define Derivative of Intensity function
//
double maxCondit(double x) {
  double  result = x - tan(x);
  return result;
}

//
//Find the roots of a function
//
Doub rootFinder(double a, double b, double tol) {
  //
  //Find roots
  //
  Doub root = zbrent(maxCondit, a, b, tol);

  return root;
}  

//
//Create table of Intensity values at various alpha values
//
void createTable() {
  //==============================================================
  // Create output file
  //==============================================================
  ofstream outfile;
  ostringstream filename;
  filename << "Alpha_Intensity_Table" << ends;
  outfile.open(filename.str().c_str());
  //==============================================================
  // Write header of output file.  Include "#" at beginning of line,
  // so that file can be read by plotting programs
  //==============================================================
  outfile.setf(ios::left);
  outfile << "#Alpha       " << "Intensity I(alpha)" << endl;

  //==============================================================
  // Find Intensities from alphas 0 to 20
  for (double x = 0; x < 20; x += 0.01) {
    double intense = intensity(x);
    outfile << setw(12) << x << setw(15) << intense << endl;
  }
  //==============================================================
  // Close output file
  //==============================================================
  outfile.close();
}



  
int main() {
  //
  //Create table of Intensity vs Alpha
  //
  createTable();
  
  //
  //Set constants for root finding method
  //
  double a;
  double b;
  double tol;

  //
  //Get rootFinder parameters
  //
  cout << "Input left bracket: " << endl;
  cin >> a;
  cout << "Input right bracket: " << endl;
  cin >> b;
  cout << "Input tolerance: " << endl;
  cin >> tol;

  //
  //Find Root
  //
  Doub root = rootFinder(a,b,tol); 
  cout << endl<<  "Root at: " << root << endl;

  //
  //Get Intensity at Root
  //
  double max = intensity(root);
  cout << "Intensity at Maxima is: " << max << endl;
  
  return 0;
}
