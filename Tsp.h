//TSP.h

#pragma once
#include "Tour.h"
using namespace std;

class TSP {

	public :
		TSP(const Tour& tour1) { tour = tour1; } 
		void runTSP();
		Tour getBest() const { return tour; }
		void display() const { cout << tour << endl; } 
		
	private :
	
		Tour tour;

};

