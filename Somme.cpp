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

void pwlfTest();


int main(){
	
	cout << "Hello ! \n";	
	/*
	string customers = "customersTest.txt";
	string preferences = "preferencesTest.txt";
	string settingsFile = "settings.txt";
	//CustomerGenerator generator(customers,preferences,5);
	SettingsGenerator settings("settings.txt");
	
	CustomerList test("customersTest.txt");
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
	
	/*cout <<"Tour test" << endl;
	Tour tour;
	tour.addCustomer(test.getCustomer(0));
	tour.addCustomer(test.getCustomer(3));
	tour.addCustomer(test.getCustomer(1));
	tour.addCustomer(test.getCustomer(2));
	
	/*PiecewiseLinearFunction fh;
	fh = tour.propagatedFunction(3);
	cout << "F3: " << endl;
	cout << fh << endl;*/
	
	pwlfTest();
	

	
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
    
void pwlfTest() {
	
	Piece P1(0,10,1,1,1);
	Piece P2(3,7,1,1,1);
	Piece P3(2,6,1,1,1);
	Piece P4(5,12,1,1,1);
	
	PiecewiseLinearFunction pwlf;
	pwlf.addPiece(P1);
	pwlf.addPiece(P2);
	pwlf.addPiece(P3);
	pwlf.addPiece(P4);
	cout << pwlf << endl;
	
	
}
    

 












