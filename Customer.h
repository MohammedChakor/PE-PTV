//Customer.h

#pragma once
#include <iostream>
#include <string>
#include<algorithm>
#include "CustomerTemplateForm.h"
#include "SettingsGenerator.h"
#include "Function.h"
#include "MatriceCarree.h"
#include "Piece.h"
#include "PiecewiseLinearFunction.h"
#include "PenaltyFunction.h"
using namespace std;

#define AVERAGESPEED 20 /* m/s */
#define WORKDAY 36000 /*10H*/
#define MAXDISTANCE 50000 /* Perimeter of less than sqrt(2*MAXDISTANCE²) around warehouse */
#define MAXSERVICE 3600 /* max service duration */
#define INFINITY 100000


class Customer
{
	public :
		Customer() {}
		Customer(const string& name, int custNumber, float x, float y, int servTime); // start end service in seconds
		string getName() const { return customerName; }
		float getX() const { return x_coord; }
		float getY() const { return y_coord; }
		int getNumber() const {return customerNumber; }
		int getServiceTime() const { return serviceTime; }
		CustomerTemplateForm getTemplate() const { return customerTemplateForm; }
		PenaltyFunction getPenalty() const { return penaltyFunction; }
		
		float getDistance(const Customer& customer2) const ;
		float getTravelTime(const Customer& customer2) const ;
		friend float distance(const Customer& customer1, const Customer& customer2);
		friend float travelTime(const Customer& customer1, const Customer& customer2);
		
		void setName(const string& newName) { customerName = newName; }
		void setX(float newX) { x_coord = newX; }
		void setY(float newY) { y_coord = newY; }
		void setNumber(int newN) { customerNumber = newN; }
		void setTemplate(CustomerTemplateForm newTemplate) { customerTemplateForm = newTemplate; }
		void displayTemplate() const { cout << customerTemplateForm << "\n"; }
		void setPenaltyFunction(const SettingsGenerator& settings);
		void displayPenalty() const { cout << penaltyFunction <<endl; }
		
		friend ostream& operator<<(ostream& flux, const Customer& customer);
		bool operator==(const Customer& customer2) const;
		bool operator!=(const Customer& customer2) const;
		
	 
		
	private :
		string customerName;
		int customerNumber;
		int serviceTime; // u sigma(h)
		float x_coord;
		float y_coord;
		
		CustomerTemplateForm customerTemplateForm; /*used to generate a penalty function */		
		PenaltyFunction penaltyFunction;	/* generated using the customerTemplateForm */	
};


/* Generates input files customers et preferences */
class CustomerGenerator {

	public :
		CustomerGenerator(const string& customersFile, const string& preferencesFile, char numerOfCustomersC);
	
	private :
		const vector<string> emphasis = {"very_much","much","rather"};
		const vector<string> preference = {"like","dislike"};
		const vector<string> gradient = {"sooner","later"};	
};
























