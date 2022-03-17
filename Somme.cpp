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
	
	CustomerList test("customers.txt");
	cout << "Affichage: " << test << "Fin Affichage \n";
	test.initTemplates("preferences.txt");
	Customer c1 = test.getCustomer(2);
	cout << c1 << "\n";
	c1.displayTemplate();
	
	Piece p1(3600,7200,-1,3);
	Piece p2(10000, 11000,3,4);
	Piece p3(10500, 11500, 7, -2);
	
	PiecewiseLinearFunction test_function;
	test_function.insertPiece(p1);
	test_function.insertPiece(p3);
	test_function.insertPiece(p2);
	
	cout << test_function << "\n";
	
    
    return 0; 
    
    }
    
    
 












