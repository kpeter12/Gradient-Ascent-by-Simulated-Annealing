// Kevin Peterson
// 10/20/18
// sa.cpp
// This program uses simulated annealing to find the maximum of a Gaussian function
// It implements a linear temperature function to allow for "bad moves" in order to find the global max 
// of the function instead of getting stuck on a local max like greedy local search does often
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "SumofGaussians.h"

using namespace std;

double runif();  //gets a random double from -.01 to .01
double getRandomStart();//returns random starting location  [1,10]
double updateTemperature(int temp);

int main(int argc, char* argv[]) {

    int seed = atoi(argv[1]);
    int dims = atoi(argv[2]);
    int ncenters = atoi(argv[3]);
  
    srand(seed);
    SumofGaussians sog(dims,ncenters);

    double input[dims]; 
	double originalInput[dims];
    double dz[dims];
	double temperature = 100000;   //temperature will start at 1000000, then go to zero linearly
	//get a random value [1,10] for each of the dimensions, e,g: x=1.43 y=8, z = 4.32
	
	//cout << "Starting input: ";
	for (int i = 0; i < dims; i++){
		input[i] = getRandomStart(); 
		originalInput[i] = input[i];
	//	cout << input[i] << " ";
	}
	//cout << "    Starting g(x): " << sog.eval(input);
	//cout << endl;
	
	int iteration = 1;
	while (iteration <= 100000)
	{
		//cout << "Iteration: " << iteration << endl;
		//make a new location with the runif
		double newLocation[dims];
		//cout << "New Location: ";
		for (int i = 0; i < dims; i++)
		{
			newLocation[i] = input[i] + runif();
		//	cout << newLocation[i] << " ";
		}
		//cout << "G(y) = " << sog.eval(newLocation)<<endl;
		

		
		//if G(Y) > G(X), accept it, else accept based on probability of temperature
		if (sog.eval(newLocation) > sog.eval(input))
		{
		//	cout << "G(Y) > G(X), accepting this location " << endl;
			for (int i = 0; i < dims; i++){
				input[i] = newLocation[i];
			}
			//print new location
			for (int i = 0; i < dims; i++)
			{
				cout << input[i] << " ";
			}
			cout << sog.eval(input) << endl;
			
		}
		else
		{
			double expVal = exp( (sog.eval(newLocation) - sog.eval(input)) / temperature);   //probablity we will take move
			//cout << "Value of Exp: " << expVal << endl;
			int probability = ceil(expVal * 100);
			//cout << "Value of Probablity: " << probability << endl;
			int randNum = rand() % 100 + 1;
			if (randNum <= probability)
			{
				//cout << "Our random number is " << randNum << " which is less than our probablity, accepting this location" << endl;
				for (int i = 0; i < dims; i++)
				{
				input[i] = newLocation[i];
				}
				for (int i = 0; i < dims; i++)
				{
					cout << input[i] << " ";
				}
				cout << sog.eval(input) << endl;
				
				
			}
			else  //else keep the same input point that we already had
			{
				//cout << "Our random number is " << randNum << " which is greater than our probablity, rejecting this location" << endl;
			}
			
			//Temperature schedule, reduce temperature by .01% every iteration until it is down to .0001 or less, then just keep temperture at virtually zero
			if (temperature <= .0001)
			{
				temperature = .0001;
			}
			else{
				temperature *= .999;
			}
			//cout << " TEMP: "<<temperature << " ";
		}
		iteration++;
	}
	
	
}

//gets a random double from -.1 to .1
double runif(){
	double temp = ((1.0*rand()) / (RAND_MAX + 1.0)); //gets random number 1-10
	return (temp * .02 - .01);   //scales to -.1, .1
}

//gets random start location 1-10
double getRandomStart() {
  return ((10.0*rand()) / (RAND_MAX + 10.0));
}