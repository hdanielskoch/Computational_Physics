//Ising Model

#include "Spins.h"

using namespace std;

int main() {
  
  
  //Initial parameters
  Doub max_Sweeps = 1000; //Number of sweeps to reach equilibria

  Doub init_Temp = 1.3;
  Doub final_Temp = 3.5;
  Doub increment = 0.01;

  //Create output file for values of M at various T
  ofstream outfile_Temp_M;
  ostringstream filename_M;
  filename_M << "M vs T" << ends;
  outfile_Temp_M.open(filename_M.str().c_str());
  outfile_Temp_M.setf(ios::left);
  outfile_Temp_M << "#M          T       " << endl;

  //Create output file for values of E at various T
  ofstream outfile_Temp_E;
  ostringstream filename_E;
  filename_E << "E vs T" << ends;
  outfile_Temp_E.open(filename_E.str().c_str());
  outfile_Temp_E.setf(ios::left);
  outfile_Temp_E << "#E          T       " << endl;
  
  //Iterate over temperatures
  for (Doub temp=init_Temp; temp< final_Temp;temp+= increment) {

    //Initiate spins array
    Spins spins;
    
    //Create  M vs Numsweeps output file
    ofstream outfile_Mag;
    ostringstream filename_MT;
    filename_MT << "M vs NumSweeps at T=" << temp << ".out" << ends;
    outfile_Mag.open(filename_MT.str().c_str());
    outfile_Mag.setf(ios::left);
    outfile_Mag << "#M          Num Sweeps" << endl;

    //Create E vs Numsweeps output file
    ofstream outfile_Eng;
    ostringstream filename_ET;
    filename_ET << "E vs NumSweeps at T=" << temp << ".out" << ends;
    outfile_Eng.open(filename_ET.str().c_str());
    outfile_Eng.setf(ios::left);
    outfile_Eng << "#E          Num Sweeps" << endl;
  
    //Iterate over each sweep
    for (int a = 1;a<max_Sweeps;a++){

      //Iterates through N randomly picked spins and flips spins
      //if Boltzman energy is greater than a random number
      spins.sweep(temp);
      spins.find_Mag_Energy();

      //Get mag and energy values for sweep
      Doub mag = spins.getMag();
      Doub eng = spins.getEnergy();

      //Store magnetism
      spins.input_Mag(mag,a);

      //Store energy
      spins.input_Eng(eng,a);
      
      //Write data to file for each sweep
      outfile_Mag << setw(12) << a << setw(10) << mag << endl;
      outfile_Eng << setw(12) << a << setw(10) << eng << endl;
    }

    //Get statistics for each temperature
    Doub avg_Mag = spins.find_Avg_Mag(max_Sweeps);
    Doub avg_Eng = spins.find_Avg_Eng(max_Sweeps);

    Doub m_Std = spins.mag_Std(avg_Mag);
    Doub e_Std = spins.eng_Std(avg_Eng);


    //Write temperature and  avg_Mag and avg_Eng to a file
    outfile_Temp_M << setw(12) << temp << setw(10) << avg_Mag << endl;
    outfile_Temp_E << setw(12) << temp << setw(10) << avg_Eng << endl;

    cout << "Temperature of " << temp << endl;
    cout << "Mag Equilibrium: " << avg_Mag << endl;
    cout << "Mag Equilibrium STD: " << m_Std << endl;
    cout << "Engery Equilibrium: " << avg_Eng << endl;
    cout << "Engery Equilibrium STD: " << e_Std << endl << endl;
  }

  return 0;
}

