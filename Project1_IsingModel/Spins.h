//Spins.h

#ifndef Spins_H
#define	Spins_H

# include "nr3.h"
# include "ran.h"

#define M 128 //Length and width of array of spins
#define N 16384

using namespace std;

class Spins {
public:
    //
    //Constructs spin array.
    //
    Spins();
    
    //
    //Prints board.
    //
    void printSpins();
    
    //
    //Find magnetization at a certain temperature
    //
    void find_Mag_Energy();

    //Sweep through array
    void sweep(Doub temp);

    //Determine whether or not to flip a spin
    bool determine_Flip(int x,int y, Doub temp);

    //Return magnetization of array
    Doub getMag() {return Magnetization;}

    //Return energy of array
    Doub getEnergy() {return Energy;}

    //Put magnetism value into array
    void input_Mag(Doub mag, int count);

    //Put energy value into array
    void input_Eng(Doub eng, int count);

    //Find the average magnetism by determining the equilibrium
    Doub find_Avg_Mag(Doub mag_Max_Sweeps);

    //Find the average energy by determining the equilibrium
    Doub find_Avg_Eng(Doub eng_Max_Sweeps);

    //Return standard deviation of magnetisim
    Doub mag_Std(Doub avg_Mag);

    //Return standard deviation of energy
    Doub eng_Std(Doub avg_Eng);

    
private:
    int SpinsArr[M][M]; //Initializes spins array
    Doub Magnetization;
    Doub Energy;
    Doub stored_M[1000];
    Doub stored_E[1000];
    Doub Mag_Eq;
    Doub Eng_Eq;
};

#endif	/* Spins_H */
