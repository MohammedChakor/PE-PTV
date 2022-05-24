// Somme.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

#include "MatriceCarree.h"
//#include "Sommet.h"
#include "Customer.h"
#include "Function.h"
using namespace std;

//void pwlfTest();
void sumTest();


int main(){
	
	cout << "Hello ! \n";	
	
	string customers = "customersTest.txt";
	string preferences = "preferencesTest.txt";
	string settingsFile = "settings.txt";
	//CustomerGenerator generator(customers,preferences,15);
	SettingsGenerator settings(settingsFile);
	
	CustomerList test(customers);
	test.initTemplates(preferences);
	test.initPenalties(settings);	

	cout <<"Tour test" << endl;
	Tour tour3(test);
	PiecewiseLinearFunction ibaraki = tour3.ibarakiFunction(tour3.getSize());


	cout << "\n\n\n\n\n" << endl;
	TSP testTSP(tour3);
	testTSP.runTSP();
	Tour best = testTSP.getBest();
	cout << best << endl;
	PiecewiseLinearFunction final0 = best.ibarakiFunction(best.getSize());
	
	cout << "Penalty before TSP: " << tour3.evaluate(ibaraki) << endl;
	cout << "Penalty after TSP: " << best.evaluate(final0) << endl;
	
	

	/*
	PiecewiseLinearFunction fh3;
	fh3 = tour3.ibarakiFunction(15);
	cout << "Random sequence \n " << fh3 << endl;	
	cout << "Argmin " << fh3.argMin() << endl;
	
	tour3.switchCustomers(1,14,2);
	cout << "Switch: "<< endl;
	cout << tour3 << endl;
    
    PiecewiseLinearFunction fh4;
	fh4 = tour3.ibarakiFunction(15);
	cout << "AfterSWitch \n " << fh4 << endl;	
	cout << "Argmin " << fh4.argMin() << endl;*/
	
    return 0; 
    
    }
    
void sumTest() {

	PiecewiseLinearFunction f0;
	Piece p0(-INFINITY,3,-1,5, 1);
	f0.insertPiece(p0);
	Piece p1(3,6,-2,2,1);
	Piece p4(6,INFINITY,1,1,1);
	f0.insertPiece(p1);
	f0.insertPiece(p4);
	cout << f0 << endl;
			
	PiecewiseLinearFunction f1;
	Piece p2(-INFINITY,4,1,1,1);
	f1.insertPiece(p2);
	Piece p3(4,8,-2,2,1);
	Piece p5(8,INFINITY,1,1,1);
	f1.insertPiece(p3);
	f1.insertPiece(p5);
	cout << f1 << endl;	
	
	PiecewiseLinearFunction f3;
	f3 = f0 + f1;
	cout << f3 << endl;
	PiecewiseLinearFunction f4;
	f4 = f3.min();
	cout << f4 << endl;
}

	
/*    
void pwlfTest() {
	
	Piece P1(0,10,1,1,1);
	Piece P2(3,7,1,1,1);
	Piece P3(2,6,1,1,1);
	Piece P4(5,12,1,1,1);
	Piece P5(0,13,1,1,1);
	Piece P6(14,16,1,1,1);
	
	PiecewiseLinearFunction pwlf;
	pwlf.addPiece(P1);
	pwlf.addPiece(P2);
	pwlf.addPiece(P3);
	pwlf.addPiece(P4);
	pwlf.addPiece(P5);
	pwlf.addPiece(P6);
	cout << pwlf << endl;
	
	cout << "Min : \n" << pwlf.min() << endl;
	
	
}*/
    

 












