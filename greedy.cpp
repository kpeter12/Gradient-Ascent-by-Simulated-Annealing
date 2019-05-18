// Kevin Peterson
// 10/20/18
// greedy.cpp
// This program finds the maximum of a Gassuian function using Greedy Local Search.
// It will find the closest maximum until the derivative of the function is < 1*e-8
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "SumofGaussians.h"

using namespace std;

double runif();  //gets a random double from -.01 to .01
double getRandomStart();//returns random starting location  [1,10]

int main(int argc, char* argv[]) {

    int seed = atoi(argv[1]);
    int dims = atoi(argv[2]);
    int ncenters = atoi(argv[3]);
  
    srand(seed);
    SumofGaussians sog(dims,ncenters);

    double input[dims]; 
	double originalInput[dims];
    double dz[dims];
	
	//get a random value [1,10] for each of the dimensions, e,g: x=1.43 y=8, z = 4.32
	//cout << "Starting input: ";
	for (int i = 0; i < dims; i++){
		input[i] = getRandomStart(); 
		originalInput[i] = input[i];
		//cout << input[i] << " ";
	}
	//cout << "    Starting g(x): " << sog.eval(input);
	///cout << endl;
	
	
	double* nextPoints;  //will hold pointers to double arrays of the next points(inputs) to move to 
	int nextMove = -1;
	bool foundMax = false;       //set to true once max is found
	int plusOrMinus = 0;     //1 for plus, 2 for minus
	while (!foundMax)
	{
		sog.deriv(input,dz);
			//cout << "Stepsize: " << stepSize << endl;
		double *newInputPlus = new double[dims];     //make new array for a new point
		double *newInputMinus = new double[dims];     //make new array for a new point
		for (int j = 0; j < dims; j++){          //copy original point into new point
			double stepSize = 0.01 * dz[j];    //(.01 * dG(x)/dx)
			newInputPlus[j] = input[j] + stepSize;
			newInputMinus[j] = input[j] - stepSize;
			
		}
		
		if (plusOrMinus == 0)
		{
			if (sog.eval(newInputPlus) >= sog.eval(newInputMinus))
				plusOrMinus = 1;
			else 
				plusOrMinus = 2;
		}
		
		if (plusOrMinus == 1)     //two arrays one moving in positive direction with stepsize, one in negative, we take which 
			nextPoints = newInputPlus;                           //direction maximizes g(x)
		else
			nextPoints = newInputMinus; 
			
		//this segment of code takes what we have
		double valueDifferences[dims];   //holds the absolute value of the difference in dgx/dx values for next moves
		double greatestChange = 0;
		double biggestDifference = 0.00000001;
		bool foundMove = false;
		
		if (sog.eval(nextPoints) - sog.eval(input) > biggestDifference)
			{
				foundMove = true;
				//copy next move into original input array 
				for (int i = 0; i < dims; i++){
					input[i] = nextPoints[i];
				}
				
				//cout << "NEW ARRAY/POINT: ";
				for (int i = 0; i < dims; i++){
					cout << input[i] << " ";
				}
				cout << sog.eval(input) << endl;
			}
		else
		{
			//cout << "Detected Max: ";
			for (int i = 0; i < dims; i++){
				cout << input[i] << " ";
			}
			cout << sog.eval(input) << endl;
			foundMax = true;
		}
		//DEALLOCATWE MEMORY HERE
		delete [] nextPoints;  //prevent memory leak
		
	}
  return 0;
}

//gets a random double from -.1 to .1
double runif(){
	double temp = ((1.0*rand()) / (RAND_MAX + 1.0)); //gets random number 1-10
	return (temp * .02 - .01);   //scales to -.01, .01
}
//gets random double 1-10, for start location
double getRandomStart() {
  return ((10.0*rand()) / (RAND_MAX + 10.0));
}