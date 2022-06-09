//SettingsGenerator.cpp

#include "SettingsGenerator.h"

using namespace std;


SettingsGenerator::SettingsGenerator() : settingsMatrix(4){ /*generates a .txt file with a format that can be used in the Matrix() constructor */

	string settingsFile;
	cout <<"Name of new settings file (name.txt) :\n";
	cin >> settingsFile;
	int temp1;
	int temp2;
	int temp3;
	int dis;
	int addis;
	int trash = 0;
	ofstream settings(settingsFile);
	cout << "Settings initialization in " << settingsFile << " for penalty function generation: \n";
	
	settings << 4 << endl; /*Matrix dimension 4x4 */
	
	cout << "Dissatisfaction value for every second of travel time: ";
	cin >> dis;	
	
	cout << "Additional dissatisfaction value when working overtime: ";
	cin >> addis;	
	
	cout << "Mapping each of „very much“, „much“ and „rather“ to an EMPHASIS value in case of „LIKE“, enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< dis << endl;
	settingsMatrix.set(0,0,temp1);
	settingsMatrix.set(0,1,temp2);
	settingsMatrix.set(0,2,temp3);
	settingsMatrix.set(0,3,dis);
	
	cout << "Mapping each of „very much“, „much“ and „rather“ to an EMPHASIS value in case of „DISLIKE“, enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< addis << endl;
	settingsMatrix.set(1,0,temp1);
	settingsMatrix.set(1,1,temp2);
	settingsMatrix.set(1,2,temp3);
	settingsMatrix.set(1,3,addis);
	
	cout << "Mapping each of „very much“, „much“ and „ratclearher“ to a GRADIENT value in case of („sooner“ and „like“) or („LATER“ and „dislike“), enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< trash << endl;
	settingsMatrix.set(2,0,temp1);
	settingsMatrix.set(2,1,temp2);
	settingsMatrix.set(2,2,temp3);
	
	cout << "Mapping each of „very much“, „much“ and „rather“ to a GRADIENT value in case of („later“ and „like“) or („SOONER“ and „dislike“), enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< trash << endl;
	settingsMatrix.set(3,0,temp1);
	settingsMatrix.set(3,1,temp2);
	settingsMatrix.set(3,2,temp3);
}


SettingsGenerator::SettingsGenerator(const string& settingsFile) : settingsMatrix(settingsFile, "momolebg"){}


