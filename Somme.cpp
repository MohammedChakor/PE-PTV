// Somme.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

#include "MatriceCarree.h"
#include "Sommet.h"
#include "Customer.h"
using namespace std;

#define INFINITY 100000
#define START 28800

int main(){
	
	cout << "Hello ! \n";	
	
	string customers = "customersTest.txt";
	string preferences = "preferencesTest.txt";
	string settingsFile = "settings.txt";
	CustomerGenerator generator(customers,preferences,10);
	SettingsGenerator settings("settings.txt");
	cout << settings.get(1,3) << endl;
	
	
	/*	
	CustomerList test(customers);
	cout << "Affichage: " << test << "Fin Affichage \n";
	test.initTemplates("preferences.txt");
	Customer c1 = test.getCustomer(2);
	cout << c1 << "\n";
	c1.displayTemplate();
	
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
    
void settings(const string settingsFile) {
	

}
 












