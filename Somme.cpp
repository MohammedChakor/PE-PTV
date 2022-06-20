// Somme.cpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include "MatriceCarree.h"
#include "Customer.h"
#include "CustomerList.h"
#include "Tour.h"
#include "Tsp.h"

using namespace std;


int main(int argc, char *argv[]){

	cout << "Settings file: " << argv[1] << "\n" << endl;
	
	
	
	string settingsFile = argv[1];
	SettingsGenerator settings(settingsFile);
	
	string customerFile = "CustomerFile" ;
	string preferenceFile = "PreferenceFile" ;
	string txt = ".txt";
	int numberOfCustomers = atoi(argv[2]);
	int numberOfSequences = atoi(argv[3]);
	
	string results = "results.txt";
	fstream file_out(results);
	
	srand (time(NULL));	
		
	for (int i = 0; i < numberOfSequences; i++) {
	
		string customerFileNumber = customerFile;
		customerFileNumber.append(to_string(i));
		customerFileNumber.append(txt);		
		string preferenceFileNumber = preferenceFile;
		preferenceFileNumber.append(to_string(i));
		preferenceFileNumber.append(txt);
		
		CustomerGenerator customers(customerFileNumber, preferenceFileNumber, numberOfCustomers);
		CustomerList customerList(customerFileNumber);
		customerList.initTemplates(preferenceFileNumber);
		customerList.initPenalties(settings);
		
		Tour sequence(customerList);
		PiecewiseLinearFunction ibaraki_sequence = sequence.ibarakiFunction(sequence.getSize());
		float inputTravelTime = sequence.getTravelTime();
		float input_score = sequence.evaluate(ibaraki_sequence);
		
		TSP tsp(sequence);
		tsp.runTSP();
		Tour output = tsp.getBest();
		PiecewiseLinearFunction ibaraki_output = output.ibarakiFunction(output.getSize());
		float output_travelTime = output.getTravelTime();
		float output_score = output.evaluate(ibaraki_output);
		
		//Ecriture résultats
		
		if(!file_out.is_open()) {
			cout << "Failed to open results.txt" << endl;
			}
		else {
			file_out << sequence.getSize() << "\t" << inputTravelTime << "\t" << input_score << "\t" << output_travelTime << "\t" << output_score << "\t" << settingsFile << endl; 
			}	
	}	
	
	file_out.close();	
		
    return EXIT_SUCCESS; 
    
    }


 












