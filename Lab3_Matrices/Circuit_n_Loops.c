//Electrical Circuit with n loops
//Solve the quations from part (a) for I_i

#include <iostream>
#include "nr3.h"
#include "ludcmp.h"
using namespace std;


void currentSolve() {
  int n; //Number of loops
  
  //Prompt for number of loops (n)
  cout << "Number of loops n= " << endl;
  cin >> n;

  //Allocate a and b matrices
  MatDoub a(n,n);
  VecDoub b(n),x(n);

  //Set Voltage to 0 from first equation
  b[0] = 0.0;

  //Set I_1 coefficient
  a[0][0] = 1.0;
  
  //Prompt user for V_1
  Doub  V_1;
  cout << "V_1=  ";
  cin >> V_1;

  //Prompt user for R_1
  Doub R_1;
  cout << "R_1= ";
  cin >> R_1;

  //
  //Prompt user for other voltages and resistances
  //Put -1 on top row (except first entry)
  //Put R_1 on first column (except first entry)
  //Put R_n on diagonal (except first entry)
  //
  Doub V_temp;
  for (int i=2; i<(n+1); i++) {
    //Prompt user for Voltages (b vector)
    cout << "Input V_" << i << " = ";
    cin >> V_temp;
    b[i-1] = V_1 + V_temp;

    //Prompt user for resistances (along diagonal)
    cout << "Input R_" << i << " = ";
    cin >> a[i-1][i-1];

    //Fill top row with -1 (Current equation)
    a[0][i-1] = -1.0;

    //Fill first column with R_1
    a[i-1][0] = R_1;  
  }
  
  //Print A
  cout << endl << "A = " <<endl;
  for (int j=0; j<n; j++) {
    for (int k=0; k<n; k++) {
      cout << a[j][k] << " ";
    }
    cout << endl;
  }

  //Print b
  cout << endl << "b= " << endl;
  for (int j=0; j<n; j++) {
    cout << b[j] << endl;
  }

  //Create Upper and Lower matrix from A
  LUdcmp alu(a);

  //Solve the matrix for currents 
  alu.solve(b,x);

  //Print out current matrix
  for (int i=0; i<n; i++) {
    cout << "I_" << i+1 << " = " << x[i] << endl;
  }

}

void problem_1d() {
  int V_1 = 1.0;
  int R_i = 1.0;

  int n; //Number of loops
  
  // Prompt for number of loops (n)
  cout << "Number of loops n= " << endl;
  cin >> n;

 
  //Allocate a and b matrices
  MatDoub a(n,n);
  VecDoub b(n),x(n);
  
  //Set Voltage to 0 from first equation
  b[0] = 0.0;

  //Set I_1 coefficient
  a[0][0] = 1.0;

  //Fill rest of a matrix and b vector
  for (int i=1; i<n; i++) {
    //Fill rest of  b vector with V_1
    b[i] = V_1;

    //Fill top row of a with -1 (currents)
    a[0][i] = -1.0;

    //Fill first column of a with R_1
    a[i][0] = R_i;

    //Fill diagonal of a with R_i
    a[i][i] = R_i;
    
  }

  //Create Upper and Lower matrix from A
  LUdcmp alu(a);

  //Solve the matrix for currents 
  alu.solve(b,x);

  cout << "Current I_1 = " << x[0] << endl; 
}

void problem_1e() {
  //
  // Create output file
  //
  ofstream outfile;
  ostringstream filename;
  filename << "I_1 vs n" << ends;
  outfile.open(filename.str().c_str());
  outfile.setf(ios::left);
  outfile << "#Number of Loops n       " << "I_1" << endl;

  //Initialize V_i and R_i
  Doub V_i = 1.0;
  Doub R_i; //R_i changes with i

  int n; //Number of loops
  
  //Iterate over the number of loops in the circuit
  //and find I_1 for each circuit
  for (n=1; n<102; n++) {
 
    //Allocate a and b matrices
    MatDoub a(n,n);
    VecDoub b(n),x(n);
    

    //Set I_1 coefficient
    a[0][0] = 1.0;

    //set b[0] to 0
    b[0]= 0.0;
  
    //Fill rest of a matrix and b vector
    for (int i=1; i<n; i++) {
      //Fill rest of  b vector with V_1 + V_i
      b[i] = V_i + V_i; //(V_1 = V_i)

      //Fill top row of a with -1 (currents)
      a[0][i] = -1.0;

      //Fill first column of a with R_1 (R_1 = 1)
      a[i][0] = 1.0;
    
    }
    //Fill diagonal of a with R_i
    for (int i=1; i<n; i++) {
      R_i = i+1;
      for (int j=1; j<n; j++) {
	if (i==j) {
	  a[i][j] = R_i;
	} else {
	  a[i][j] = 0.0;
	}
      }
    }

    //Create Upper and Lower matrix from A
    LUdcmp alu(a);

    //Solve the matrix for currents 
    alu.solve(b,x);

    //Write I_1 to a file (n=i+1) - Can't have 0 loops
    if (n!=1) {
      outfile << setw(25) << n-1  << setw(15) << x[0]  << endl;
    }
  }      
}


int main() {
  currentSolve();
  
  problem_1d();

  problem_1e();

}
	      
