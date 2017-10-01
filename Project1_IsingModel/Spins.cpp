//Spins.cpp
//Creates an array of spins that can be swept through

//All functions are performed on the class Spins

# include "nr3.h"
# include "Spins.h"

using namespace std;

//Fill array
Spins::Spins() {
  
  //Fill array with +1
  for (int i=0;i<M;i++){
    for (int j = 0; j < M; j++){
      SpinsArr[i][j]=1;
    }
  }
}

//Print spin array
void Spins::printSpins() {
  for (int i=0; i<M; i++){
    for (int j=0; j<M; j++){
      cout << SpinsArr[i][j] << " ";
    }
    cout << endl;
  }
}

//Find the magnetization and energy of the array
void Spins::find_Mag_Energy() {
  int sum_spins = 0;
  int sum_neighbor = 0;

  //Iterate over array
  for (int i=0;i<M;i++){
    for (int j = 0; j < M; j++){

      //Add spin
      sum_spins += SpinsArr[i][j];

      //Add neighbors
      int right,bottom;

      //Use periodic boundary conditions
      if (i==M-1){
	right = SpinsArr[0][j];
      }
      else{
	right = SpinsArr[i+1][j];
      }
      if (j==M-1){
	bottom = SpinsArr[i][0];
      }
      else{
	bottom = SpinsArr[i][j+1];
      }
            
      sum_neighbor += SpinsArr[i][j]*(right + bottom);
    }
  }
  //Calculate magnetization and energy of array
  Magnetization = ((double)sum_spins)/((double)(M*M));
  Energy = -((double)sum_neighbor)/((double)(M*M));
}

//Sweep through array, pick N random spins,
//and decide whether or not to flip them
void Spins::sweep(Doub temp) {
  //Get random x_cordinate
  Doub ran_seed_x = clock();
  Ran ran_x(ran_seed_x);

  //Get random y_cordinate
  Doub ran_seed_y = 2*clock();
  Ran ran_y(ran_seed_y);

  //Iterate through N randomly picked spins
  for (int i = 0; i < N; i++){
    Doub ran_number_x = ran_x.doub();
    Doub ran_number_y = ran_y.doub();

    //Get coordinates between 0 and M
    int x_rand = ran_number_x * M;
    int y_rand = ran_number_y * M;

    //Determine whether to flip spin
    bool flip = determine_Flip(x_rand,y_rand,temp);
    if (flip==true) {
       SpinsArr[x_rand][y_rand] = -SpinsArr[x_rand][y_rand];
    }
  }
}

//Decide whether or not to flip a spin
//Return true if spin should be flipped
bool Spins::determine_Flip(int x,int y,Doub temp) {

  //Determine spins of nearest neighbors
  
  //Initialize neighbors
  int left, right, top, bottom;

  //Use periodic boundary conditions
  //Left neighbor
  if (x==0){
    left = SpinsArr[M-1][y];
  }
  else{
    left = SpinsArr[x-1][y];
  }

  //Right neighbor
  if (x == (M-1)){
    right = SpinsArr[0][y];
  }
  else{
    right = SpinsArr[x+1][y];
  }
	
  //Top neighbor
  if (y==0){
    top = SpinsArr[x][M-1];
  }
  else{
    top = SpinsArr[x][y-1];
  }

  //Bottom neighbor
  if (y==M-1){
    bottom = SpinsArr[x][0];
  }
  else{
    bottom = SpinsArr[x][y+1];
  }

  //Change in energy if sign was flipped
  int dE = 2*SpinsArr[x][y]*(right+left+top+bottom);

  //Get random number to compare to boltzman constant
  Doub ran_seed_boltz = 3*clock();
  Ran ran_boltz(ran_seed_boltz);
  Doub ran_number_boltz = ran_boltz.doub();

  //Calculute beta (1/kT where k=1)
  Doub beta = 1.0 / temp;

  //Spin should be flipped
  if (ran_number_boltz < exp(-beta*dE)){
    return true;
  }
  //Spin should not be flipped
  else{
    return false;
  }
}

//Input magnetism value into array
void Spins::input_Mag(Doub mag, int a) {
  stored_M[a] = mag;
}

//Input energy value into array
void Spins::input_Eng(Doub eng, int a) {
  stored_E[a] = eng;
}

//Find the Average magnetism in equilibrium
Doub Spins::find_Avg_Mag(Doub mag_Max_Sweeps) {
  //Iterate through each sweet starting at sweep 100
  for (int p=100; p<mag_Max_Sweeps; p++){
    Doub avg_sum = 0;

    //Determine when equilibrium is reached
    for (int v=0;v<100;v++){
      avg_sum+=stored_M[v+p-100]; //Calculate the sum of previous 100 results
    }

    //Magnetism is near average of last 100 sweeps
    if (abs(stored_M[p]-avg_sum/100) < 0.01) { 
      Mag_Eq = p;
      return stored_M[p];	 //Return average magnetism
    }
  }
  //Equilibrium was not reached
  cout << "Need to increase the number of sweeps!" << endl;
  return 0.0;
}

//Find the average energy in equilibrium
Doub Spins::find_Avg_Eng(Doub eng_Max_Sweeps) {
  //Iterate through each sweep starting at sweep 100
  for (int p=100;p<eng_Max_Sweeps;p++){
    Doub avg_sum = 0;

    //Determine when equilibrium is reached
    for (int v=0;v<100;v++){
      avg_sum+=stored_E[v+p-100]; //Calculate the sum of previous 100 results
    }

    //Energy is near average of last 100 sweeps
    if (abs(stored_E[p]-avg_sum/100)<0.01){	
      Eng_Eq = p;
      return stored_E[p];	 //Return average energy
    }
  }
  //Equilibrium was not reached
  cout << "Need to increase the number of sweeps!" << endl;
  return 0.0;
}

//Calculate STD for Mag
Doub Spins::mag_Std(Doub avg_Mag) {

  Doub mag_Std_Tot = 0.0;

  //Calculate standard deviation from 100 points before Mag_Eq
  Doub mag_Init = Mag_Eq - 100.0;

  //Iterate through energy array
  for (int i=mag_Init; i<Mag_Eq; i++){
    
    //Get the sum of the square of the mag - avg_Mag
    mag_Std_Tot += (stored_M[i]-avg_Mag)*(stored_M[i]-avg_Mag);
  }

  //Calculuate STD for mag
  Doub mag_Std = sqrt(mag_Std_Tot/(100));
  return mag_Std;
}

//Calculate STD for Eng
Doub Spins::eng_Std(Doub avg_Eng) {

  Doub eng_Std_Tot = 0.0;

   //Calculate standard deviation from 100 points before Eng_Eq
  Doub eng_Init = Eng_Eq - 100.0;

  //Iterate through energy array
  for (int i=eng_Init;i<Eng_Eq;i++){
    //Get the sum of the square of the eng - avg_Eng
    eng_Std_Tot += (stored_E[i]-avg_Eng)*(stored_E[i]-avg_Eng);
  }

  //Calculuate STD for eng
  Doub eng_Std = sqrt(eng_Std_Tot/(100));
  return eng_Std;
}

