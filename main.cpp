/*
Christopher Ciobanu
Professor Chadi
Comp 151 Artificial Intelligence
11/28/21

Project 3 - Perceptrons

***** Make sure to expand the window to see all comments, some are pushed back to look neater*****
*/

#include <iostream>			//	|
#include <string>			//	|
#include <limits>			//	| 	All the libraries needed for the program to work.
#include <iomanip>			//	|					
#include <windows.h>		//	|
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>
#include <ctime>

using namespace std;



float  trueRandom() {		// this functions returns a random number 1 and 0 to populate the initial weights

	return (float)rand() / RAND_MAX;

}

vector<float> normalize(vector<float> vec, float num, float den) {		// this function normalizes the lat and long data
	float x = 0;
	vector<float> vecN;
	for (int i = 0; i < vec.size(); i++) {
		x = (vec[i] - (num)) / den;
		vecN.push_back(x);

	}

	return vecN;

}

class perceptron {		// this class defines my chromosome

private:

	vector<float> weights;		// this is the vector that stores the weights
	float stop;

public:

	perceptron()		// initilaizes class
	{

		stop = 0;
	}

	perceptron(float stop1)        //  |    This allows the variables to be updated.
	{
		stop = stop1;
	}

	void setStop(float stop1) { stop = stop1; }     //  |   these functions allow me to call and change the chomrosome defintions


	float getStop() { return stop; }


	void init() {		// initializes rates randomly
		for (int i = 0; i < 20; i++) {
			weights.push_back(trueRandom());
		}
	}

	void init1() {			// initializes weights from a data sheet
		string filename;
		float x;
		ifstream myfile1;
		do {		// code that makes sure correct file is being opened
			cout << "Please Enter the filename containing the inital weights: " << endl;
			cin >> filename;
			cin.clear();
			cin.ignore(128, '\n');
			myfile1.open(filename);

			if (!myfile1) {
				cout << "Unable to open file!" << endl;
			}

		} while (!myfile1);

		while (myfile1 >> x ) {		// reads in txt data and stores in vectors
			weights.push_back(x);
		}
		myfile1.close();
	}


	void perceptron1(vector<float> vec1, vector<float> vec2, vector<string> vec3, float thresh, float lr, float conv) {		// This is the main function that updates the weights based on the input data, and input variables
		float key[10] = { 0,0,0,0,0,0,0,0,0,0 };		//this is the key that will tell my program if it is producing the right answer 
		float Africa, America, Antartica, Asia, Australia, Europe, Arctic, Atlantic, Indian, Pacific;
		vector<float> weightsN;		// use this array to compare the previous weights with the updated ones to check for convergence leter on

		weightsN.clear();
		for (int a = 0; a < weights.size(); a++) {		// populates the new array
			weightsN.push_back(weights[a]);
		}

		for (int i = 0; i < vec1.size(); i++) {				// this for block basically checks the colom telling what continent the lat/long belong to and assigns a key to equal 1, if that coniditon is true
			if (vec3[i] == "Africa") {
				key[0] = 1; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "America") {
				key[0] = 0; key[1] = 1; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Antartica") {
				key[0] = 0; key[1] = 0; key[2] = 1;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Asia") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 1;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Australia") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 1;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Europe") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 1;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Arctic") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 1;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Atlantic") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 1;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Indian") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 1;  key[9] = 0;
			}
			else if (vec3[i] == "Pacific") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 1;
			}

			Africa = vec1[i] * weights[0] + vec2[i] * weights[1];			// this chunk updates the output for each nueron based on the weights and input data
			America = vec1[i] * weights[2] + vec2[i] * weights[3];
			Antartica = vec1[i] * weights[4] + vec2[i] * weights[5];
			Asia = vec1[i] * weights[6] + vec2[i] * weights[7];
			Australia = vec1[i] * weights[8] + vec2[i] * weights[9];
			Europe = vec1[i] * weights[10] + vec2[i] * weights[11];
			Arctic = vec1[i] * weights[12] + vec2[i] * weights[13];
			Atlantic = vec1[i] * weights[14] + vec2[i] * weights[15];
			Indian = vec1[i] * weights[16] + vec2[i] * weights[17];
			Pacific = vec1[i] * weights[18] + vec2[i] * weights[19];

			if (Africa < thresh) {					// this chunk of if statements checks to see if the previous output is greater than or less than the threshold and then outputs a 0 or 1 depending
				Africa = 0;
			}
			else if (Africa >= thresh) {
				Africa = 1;
			}
			if (America < thresh) {
				America = 0;
			}
			else if (America >= thresh) {
				America = 1;
			}
			if (Antartica < thresh) {
				Antartica = 0;
			}
			else if (Antartica >= thresh) {
				Antartica = 1;
			}
			if (Asia < thresh) {
				Asia = 0;
			}
			else if (Asia >= thresh) {
				Asia = 1;
			}
			if (Australia < thresh) {
				Australia = 0;
			}
			else if (Australia >= thresh) {
				Australia = 1;
			}
			if (Europe < thresh) {
				Europe = 0;
			}
			else if (Europe >= thresh) {
				Europe = 1;
			}
			if (Arctic < thresh) {
				Arctic = 0;
			}
			else if (Arctic >= thresh) {
				Arctic = 1;
			}
			if (Atlantic < thresh) {
				Atlantic = 0;
			}
			else if (Atlantic >= thresh) {
				Atlantic = 1;
			}
			if (Indian < thresh) {
				Indian = 0;
			}
			else if (Indian >= thresh) {
				Indian = 1;
			}
			if (Pacific < thresh) {
				Pacific = 0;
			}
			else if (Pacific >= thresh) {
				Pacific = 1;
			}


			if (Africa != key[0]) {			// using the previous outpout, if the output does not match the key that was assigned earlier, then that means the output was wrong and the weights are updated
				weights[0] = weights[0] + lr * (key[0] - Africa) * vec1[i];		// weights are updated based on the input vector, learning rate, and previous weight
				weights[1] = weights[1] + lr * (key[0] - Africa) * vec2[i];
			}
			if (America != key[1]) {
				weights[2] = weights[2] + lr * (key[1] - America) * vec1[i];
				weights[3] = weights[3] + lr * (key[1] - America) * vec2[i];
			}
			if (Antartica != key[2]) {
				weights[4] = weights[4] + lr * (key[2] - Antartica) * vec1[i];
				weights[5] = weights[5] + lr * (key[2] - Antartica) * vec2[i];
			}
			if (Asia != key[3]) {
				weights[6] = weights[6] + lr * (key[3] - Asia) * vec1[i];
				weights[7] = weights[7] + lr * (key[3] - Asia) * vec2[i];
			}		
			if (Australia != key[4]) {
				weights[8] = weights[8] + lr * (key[4] - Australia) * vec1[i];
				weights[9] = weights[9] + lr * (key[4] - Australia) * vec2[i];
			}
			if (Europe != key[5]) {
				weights[10] = weights[10] + lr * (key[5] - Europe) * vec1[i];
				weights[11] = weights[11] + lr * (key[5] - Europe) * vec2[i];
			}
			if (Arctic != key[6]) {
				weights[12] = weights[12] + lr * (key[6] - Arctic) * vec1[i];
				weights[13] = weights[13] + lr * (key[6] - Arctic) * vec2[i];
			}
			if (Atlantic != key[7]) {
				weights[14] = weights[14] + lr * (key[7] - Atlantic) * vec1[i];
				weights[15] = weights[15] + lr * (key[7] - Atlantic) * vec2[i];
			}
			if (Indian != key[8]) {
				weights[16] = weights[16] + lr * (key[8] - Indian) * vec1[i];
				weights[17] = weights[17] + lr * (key[8] - Indian) * vec2[i];
			}
			if (Pacific != key[9]) {
				weights[18] = weights[18] + lr * (key[9] - Pacific) * vec1[i];
				weights[19] = weights[19] + lr * (key[9] - Pacific) * vec2[i];
			}

		}

		// outside of the for loop, all the weights are comapred to their previous weight, and if each weight difference is less than the convergence value, a stop variable is set to 1.

		if ((abs(weightsN[0] - weights[0]) < conv) && (abs(weightsN[1] - weights[1]) < conv) && (abs(weightsN[2] - weights[2]) < conv) && (abs(weightsN[3] - weights[3]) < conv) &&
			(abs(weightsN[4] - weights[4]) < conv) && (abs(weightsN[5] - weights[5]) < conv) && (abs(weightsN[6] - weights[6]) < conv) && (abs(weightsN[7] - weights[7]) < conv) &&
			(abs(weightsN[8] - weights[8]) < conv) && (abs(weightsN[9] - weights[9]) < conv) && (abs(weightsN[10] - weights[10]) < conv) && (abs(weightsN[11] - weights[11]) < conv) &&
			(abs(weightsN[12] - weights[12]) < conv) && (abs(weightsN[13] - weights[13]) < conv) && (abs(weightsN[14] - weights[14]) < conv) && (abs(weightsN[15] - weights[15]) < conv) &&
			(abs(weightsN[16] - weights[16]) < conv) && (abs(weightsN[17] - weights[17]) < conv) && (abs(weightsN[18] - weights[18]) < conv) && (abs(weightsN[19] - weights[19]) < conv)) {

			setStop(1);
		}

		else {
			setStop(0);
		}


	}



	void print() {		// this functions will print the weights at any given time for each neuron
		
			cout <<"Africa: " << "			Lat: " <<weights[0] << "		Long: " <<	weights[1] << endl;
			cout << "America: " << "			Lat: " << weights[2] << "		Long: " << weights[3] << endl;
			cout << "Antartica: " << "			Lat: " << weights[4] << "		Long: " << weights[5] << endl;
			cout << "Asia: " << "				Lat: " << weights[6] << "		Long: " << weights[7] << endl;
			cout << "Australia: " << "			Lat: " << weights[8] << "		Long: " << weights[9] << endl;
			cout << "Europe: " << "			Lat: " << weights[10] << "		Long: " << weights[11] << endl;
			cout << "Arctic: " << "			Lat: " << weights[12] << "		Long: " << weights[13] << endl;
			cout << "Atlantic: " << "			Lat: " << weights[14] << "		Long: " << weights[15] << endl;
			cout << "Indian: " << "			Lat: " << weights[16] << "		Long: " << weights[17] << endl;
			cout << "Pacific: " << "			Lat: " << weights[18] << "		Long: " << weights[19] << endl;
}

	void NN(vector<float> vec1, vector<float> vec2, vector<string> vec3, float thresh, float lr, float conv) {		// This function simply runs the data against the final weights gotten from the previous function
		float key[10] = { 0,0,0,0,0,0,0,0,0,0 };
		float Africa = 0 , America=0, Antartica=0, Asia=0, Australia=0, Europe=0, Arctic=0, Atlantic=0, Indian=0, Pacific=0;
		float Africa1 = 0, America1 = 0, Antartica1 = 0, Asia1 = 0, Australia1 = 0, Europe1 = 0, Arctic1 = 0, Atlantic1 = 0, Indian1 = 0, Pacific1 = 0;
		float Africa2 = 0, America2 = 0, Antartica2 = 0, Asia2 = 0, Australia2 = 0, Europe2 = 0, Arctic2 = 0, Atlantic2 = 0, Indian2 = 0, Pacific2 = 0;
		float Africa3 = 0, America3 = 0, Antartica3 = 0, Asia3 = 0, Australia3 = 0, Europe3 = 0, Arctic3 = 0, Atlantic3 = 0, Indian3 = 0, Pacific3 = 0;
		float correct = 0;
		float mNeurons = 0;
		float zNeurons = 0;

		for (int i = 0; i < vec1.size(); i++) {
			Africa = 0, America = 0, Antartica = 0, Asia = 0, Australia = 0, Europe = 0, Arctic = 0, Atlantic = 0, Indian = 0, Pacific = 0;

			if (vec3[i] == "Africa") {
				key[0] = 1; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "America") {
				key[0] = 0; key[1] = 1; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Antartica") {
				key[0] = 0; key[1] = 0; key[2] = 1;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Asia") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 1;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Australia") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 1;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Europe") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 1;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Arctic") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 1;  key[7] = 0;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Atlantic") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 1;  key[8] = 0;  key[9] = 0;
			}
			else if (vec3[i] == "Indian") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 1;  key[9] = 0;
			}
			else if (vec3[i] == "Pacific") {
				key[0] = 0; key[1] = 0; key[2] = 0;  key[3] = 0;  key[4] = 0;  key[5] = 0;  key[6] = 0;  key[7] = 0;  key[8] = 0;  key[9] = 1;
			}

			Africa = vec1[i] * weights[0] + vec2[i] * weights[1];
			America = vec1[i] * weights[2] + vec2[i] * weights[3];
			Antartica = vec1[i] * weights[4] + vec2[i] * weights[5];
			Asia = vec1[i] * weights[6] + vec2[i] * weights[7];
			Australia = vec1[i] * weights[8] + vec2[i] * weights[9];
			Europe = vec1[i] * weights[10] + vec2[i] * weights[11];
			Arctic = vec1[i] * weights[12] + vec2[i] * weights[13];
			Atlantic = vec1[i] * weights[14] + vec2[i] * weights[15];
			Indian = vec1[i] * weights[16] + vec2[i] * weights[17];
			Pacific = vec1[i] * weights[18] + vec2[i] * weights[19];

			if (Africa < thresh) {
				Africa = 0;
			}
			else if (Africa >= thresh) {
				Africa = 1;
			}
			 if (America < thresh) {
				America = 0;
			}
			else if (America >= thresh) {
				America = 1;
			}
			 if (Antartica < thresh) {
				Antartica = 0;
			}
			else if (Antartica >= thresh) {
				Antartica = 1;
			}
			 if (Asia < thresh) {
				Asia = 0;
			}
			else if (Asia >= thresh) {
				Asia = 1;
			}
			 if (Australia < thresh) {
				Australia = 0;
			}
			else if (Australia >= thresh) {
				Australia = 1;
			}
			 if (Europe < thresh) {
				Europe = 0;
			}
			else if (Europe >= thresh) {
				Europe = 1;
			}
			 if (Arctic < thresh) {
				Arctic = 0;
			}
			else if (Arctic >= thresh) {
				Arctic = 1;
			}
			 if (Atlantic < thresh) {
				Atlantic = 0;
			}
			else if (Atlantic >= thresh) {
				Atlantic = 1;
			}
			 if (Indian < thresh) {
				Indian = 0;
			}
			else if (Indian >= thresh) {
				Indian = 1;
			}
			 if (Pacific < thresh) {
				Pacific = 0;
			}
			else if (Pacific >= thresh) {
				Pacific = 1;
			}

			//****************** The below if statements are all to calculate and keep track of if the neurons fired correctly or incorrectly

			 // checks for number of correct fires
			 if (key[0] == Africa && key[1] == America && key[2] == Antartica && key[3] == Asia && key[4] == Australia && key[5] == Europe && key[6] == Arctic && key[7] == Atlantic && key[8] == Indian && key[9] == Pacific) {
				 correct += 1;
			 }
			 // checks for number of multiple fires
			 if ((Africa + America + Antartica + Asia + Australia + Europe + Arctic + Atlantic + Indian + Pacific)>1) {
				 mNeurons += 1;
			 }
			 //checks for number of 0 fires
			 if ((Africa + America + Antartica + Asia + Australia + Europe + Arctic + Atlantic + Indian + Pacific) == 0) {
				 zNeurons += 1;
			 }
			 //********************

			 // These statements will checks for the stats of individual neurons

			 //checks for number of correct fire
			 if (Africa == key[0]) {
				 Africa1 += 1;
			 }
			 if (America == key[1]) {
				 America1 += 1;
			 }
				 if (Antartica == key[2]) {
					 Antartica1 += 1;

				 }
				 if (Asia == key[3]) {
					 Asia1 += 1;
				 }
				 if (Australia == key[4]) {
					 Australia1 += 1;
				 }
				 if (Europe == key[5]) {
					 Europe1 += 1;
				 }
				 if (Arctic == key[6]) {
					 Arctic1 += 1;

				 }
				 if (Atlantic == key[7]) {
					 Atlantic1 += 1;
				 }
				 if (Indian == key[8]) {
					 Indian1 += 1;
				 }
				 if (Pacific == key[9]) {
					 Pacific1 += 1;
				 }
				 //******************

				 //checks for number of miss fire

				 if (Africa == 1 && key[0] == 0) {
					 Africa2 += 1;
				 }
				 if (America == 1 && key[1] == 0) {
					 America2 += 1;
				 }
					 if (Antartica == 1 && key[2] == 0) {
						 Antartica2 += 1;

					 }
					 if (Asia == 1 && key[3] == 0) {
						 Asia2 += 1;
					 }
					 if (Australia == 1 && key[4 == 0]) {
						 Australia2 += 1;
					 }
					 if (Europe == 1 && key[5] == 0) {
						 Europe2 += 1;
					 }
					 if (Arctic == 1 && key[6] == 0) {
						 Arctic2 += 1;

					 }
					 if (Atlantic == 1 && key[7] == 0) {
						 Atlantic2 += 1;
					 }
					 if (Indian == 1 && key[8] == 0) {
						 Indian2 += 1;
					 }
					 if (Pacific == 1 && key[9] == 0) {
						 Pacific2 += 1;
					 }

					 //******

					 //checks for number of failed fires
					 if (Africa == 0 && key[0] == 1) {
						 Africa3 += 1;
					 }
					 if (America == 0 && key[1] == 1) {
						 America3 += 1;
					 }

						 if (Antartica == 0 && key[2] == 1) {
							 Antartica3 += 1;

						 }
						 if (Asia == 0 && key[3] == 1) {
							 Asia3 += 1;
						 }
						 if (Australia == 0 && key[4 == 1]) {
							 Australia3 += 1;
						 }
						 if (Europe == 0 && key[5] == 1) {
							 Europe3 += 1;
						 }
						 if (Arctic == 0 && key[6] == 1) {
							 Arctic3 += 1;

						 }
						 if (Atlantic == 0 && key[7] == 1) {
							 Atlantic3 += 1;
						 }
						 if (Indian == 0 && key[8] == 1) {
							 Indian3 += 1;
						 }
						 if (Pacific == 0 && key[9] == 1) {
							 Pacific3 += 1;
						 }

					 }

					 // displays all the statistics of the neurons
					 cout << "Percentage of Examples Perfectly Classified: " << (correct / vec1.size()) * 100 << "%" << endl;
					 cout << "Percentage of Examples Caused Multiple Neurons to Fire: " << (mNeurons / vec1.size()) * 100 << "%" << endl;
					 cout << "Percentage of Examples Caused Zero Neurons to Fire: " << (zNeurons / vec1.size()) * 100 << "%" << endl;
					 cout << "Africa: " << endl << "		Fired Correctly: " << (Africa1 / vec1.size()) * 100 << "%" << endl << "		Fired Incorrectly: " << (Africa2 / vec1.size()) * 100 << "%" << endl << "		Failed to Fire: " << (Africa3 / vec1.size()) * 100 << "%" << endl
						 << "America: " << endl << "		Fired Correctly: " << (America1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (America2 / vec1.size()) * 100 << "%" << endl << "		Failed to Fire: " << (America3 / vec1.size()) * 100 << "%" << endl
						 << "Antartica: " << endl << "		Fired Correctly: " << (Antartica1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Antartica2 / vec1.size()) * 100 << "%" << endl << "		Failed to Fire: " << (Antartica3 / vec1.size()) * 100 << "%" << endl
						 << "Asia: " << endl << "		Fired Correctly: " << (Asia1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Asia2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire: " << (Asia3 / vec1.size()) * 100 << "%" << endl
						 << "Australia: " << endl << "		Fired Correctly: " << (Australia1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Australia2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire: " << (Australia3 / vec1.size()) * 100 << "%" << endl
						 << "Europe: " << endl << "		Fired Correctly: " << (Europe1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Europe2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire: " << (Europe3 / vec1.size()) * 100 << "%" << endl
						 << "Arctic: " << endl << "		Fired Correctly: " << (Arctic1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Arctic2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire: " << (Arctic3 / vec1.size()) * 100 << "%" << endl
						 << "Atlantic: " << endl << "		Fired Correctly: " << (Atlantic1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Atlantic2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire: " << (Atlantic3 / vec1.size()) * 100 << "%" << endl
						 << "Indian: " << endl << "		Fired Correctly:  " << (Indian1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly:  " << (Indian2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire:  " << (Indian3 / vec1.size()) * 100 << "%" << endl
						 << "Pacific: " << endl << "		Fired Correctly: " << (Pacific1 / vec1.size()) * 100 << "%" << endl << "		Fired InCorrectly: " << (Pacific2 / vec1.size()) * 100 << "%" << endl << "		Failed To Fire: " << (Pacific3 / vec1.size()) * 100 << "%" << endl;

				 }


 void store() {
	 ofstream myfile3;
	 string filename;
	 do {		// code that makes sure correct file is being opened
		 cout << "Please Enter the filename where you would like to store the Final Weights or hit 'x' to skip: " << endl;
		 cin >> filename;
		 cin.clear();
		 cin.ignore(128, '\n');
		 myfile3.open(filename);

		 if (!myfile3) {
			 cout << "Unable to open file!" << endl;
		 }

	 } while (!myfile3 && filename != "x");

	  myfile3 << "Final Weights of Lat and Long for each Neuron after Convergence: " << endl;
	  myfile3 <<  "Africa: " << "			Lat: " << weights[0] << "		Long: " << weights[1] << endl;
	  myfile3 << "America: " << "			Lat: " << weights[2] << "		Long: " << weights[3] << endl;
	  myfile3 << "Antartica: " << "			Lat: " << weights[4] << "		Long: " << weights[5] << endl;
	  myfile3 << "Asia: " << "				Lat: " << weights[6] << "		Long: " << weights[7] << endl;
	  myfile3 << "Australia: " << "			Lat: " << weights[8] << "		Long: " << weights[9] << endl;
	  myfile3 << "Europe: " << "			Lat: " << weights[10] << "		Long: " << weights[11] << endl;
	  myfile3 << "Arctic: " << "			Lat: " << weights[12] << "		Long: " << weights[13] << endl;
	  myfile3 << "Atlantic: " << "			Lat: " << weights[14] << "		Long: " << weights[15] << endl;
	  myfile3 << "Indian: " << "			Lat: " << weights[16] << "		Long: " << weights[17] << endl;
	  myfile3 << "Pacific: " << "			Lat: " << weights[18] << "		Long: " << weights[19] << endl;
	 
	  myfile3.close();
	 
	}

};

int main()					//	|  Main functions that ties together all the headers and functions
{
	srand((unsigned)time(NULL));
	string filename;	
	float thresh = 0.3;			//Threshhold variable
	float lr = 0.3;				//Learning Rate Variable
	float conv = 0.14;			// Convergence Variable
	int i = 0;
	int choice;
	int gen = 0;


	vector<float> vec1, vec2, vec1N, vec2N;	// vectors to store data from txt file
	vector<float> vec1T, vec2T, vec1NT, vec2NT;
	vector<string> vec3,vec3T;		// vectors to store data from txt file
	float x, y,x1,y1;
	string z,z1;

	perceptron get;

	cout << "Welcome to the Perceptron Program" << endl << "This program was created by Christopher Ciobanu, for Comp 151." << endl << "Click any button to begin!" << endl << endl;
	system("pause");

	do {
		cout << "If you would like to load in the initial weights from a file, press 1" << endl << "If you would like the initial weights to be randomly generated, press 2" << endl;
		cin >> choice;
	} while (choice != 1 && choice != 2);

	if (choice == 1) {
		get.init1();

	}
	else if (choice == 2) {
		get.init();		// initializes weight vector
	}


	ifstream myfile;
	do {		// code that makes sure correct file is being opened
		cout << "Please Enter the filename containing the training data: " << endl;
		cin >> filename;
		cin.clear();
		cin.ignore(128, '\n');
		myfile.open(filename);

		if (!myfile) {
			cout << "Unable to open file!" << endl;
		}

	} while (!myfile);

	cout << "Reading in File Data!" << endl;

	while (myfile >> x >> y >> z) {		// reads in txt data and stores in vectors
		vec1.push_back(x);
		vec2.push_back(y);
		vec3.push_back(z);
	}

	vec1N = normalize(vec1, -90, 180);		//normalizes data
	vec2N = normalize(vec2, -180, 360);		//normalizes data



	

	do {
		get.perceptron1(vec1N, vec2N, vec3, thresh, lr, conv);		// goes through and changed weights until convergence
		gen += 1;
		if (gen == 200) {			// for sake of time, stops loop after 200 epochs or runs
			break;
		}
		cout << "Epoch: " << gen << endl;

	} while (get.getStop() != 1);





	cout << endl << "Final Weights are: " << endl << endl;
	get.print();
	cout << "Total Epochs: " << gen << endl << endl;

	get.store();

	ifstream myfile1;
	do {		// code that makes sure correct file is being opened
		cout << "Please Enter the filename containing the testing data: " << endl;
		cin >> filename;
		cin.clear();
		cin.ignore(128, '\n');
		myfile1.open(filename);

		if (!myfile1) {
			cout << "Unable to open file!" << endl;
		}

	} while (!myfile1);

	
	while (myfile1 >> x1 >> y1 >> z1) {		// reads in txt data and stores in vectors
		vec1T.push_back(x1);
		vec2T.push_back(y1);
		vec3T.push_back(z1);
	}
	vec1NT = normalize(vec1T, -90, 180);		//normalizes data
	vec2NT = normalize(vec2T, -180, 360);		//normalizes data

	cout << "Running Final weights Through Neural Network: " << endl << endl;
	get.NN(vec1NT, vec2NT, vec3T, thresh, lr, conv);




	myfile.close();			// closes txt file
	myfile1.close();			// closes txt file
	system("Pause");		//	| Pauses the console
	return 0;				//	| Tells the program it can terminate.
}