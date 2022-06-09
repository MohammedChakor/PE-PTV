//SettingsGenerator.h

#pragma once 
#include "MatriceCarree.h"
#include <fstream>
using namespace std;

class SettingsGenerator {
	
	public :
		SettingsGenerator();
		SettingsGenerator(const string& settingsFile);
		int get(int i, int j) const { return settingsMatrix.get(i,j); }
	
	private :
		MatriceCarree settingsMatrix;
};

