// Somme.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

#include "MatriceCarree.h"
#include "Sommet.h"
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
	//CustomerGenerator generator(customers,preferences,5);
	SettingsGenerator settings(settingsFile);
	
	CustomerList test(customers);
	test.initTemplates(preferences);
	test.initPenalties(settings);	
	//cout << test << endl;
	
	/*
	cout << "Test min et offSet" << endl;
	Customer c1 = test.getCustomer(1);
	PenaltyFunction testf = c1.getPenalty();
	cout << testf << endl;
	cout << "min" << endl;
	cout << testf.min() << endl;
	cout << "test offset"<< endl;
	cout << testf.offSet(10) << endl;*/
	
	cout <<"Tour test" << endl;
	Tour tour;
	tour.addCustomer(test.getCustomer(0));
	tour.addCustomer(test.getCustomer(3));
	//tour.addCustomer(test.getCustomer(1));
	//tour.addCustomer(test.getCustomer(2));
	
	PiecewiseLinearFunction fh;
	fh = tour.propagatedFunction(2);
	cout << "F3: " << endl;
	cout << fh << endl;
	
	//sumTest();
	

	
	/*
	cout <<"\n*****Test PWLF Class \n";
	
	Piece p1(3600,7200,-1,3);
	Piece p2(10000, 11000,3,4);
	Piece p3(7000, 11500, 7, -2);
	
	cout<<"Test of pwlf::insertPiece() method \n\n";
	PiecewiseLinearFunction test_function;
	test_function.insertPiece(p1);
	test_function.insertPiece(p3);
	test_function.insertPiece(p2);
	cout << test_function << "\n";
	
	cout << "Test of pwlf::addPiece() method \n";
	PiecewiseLinearFunction test2;
	test2.addPiece(p1);
	test2.addPiece(p3);
	test2.addPiece(p2);
	cout << test2 << "\n";*/
	
    
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
    

 












