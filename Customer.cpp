//Customer.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Customer.h"

using namespace std;

/* Customer */
Customer::Customer(const string& name, int custNumber, float x, float y, int servTime ) {
	
	
	customerName  = name; 
	customerNumber = custNumber;
	x_coord = x;
	y_coord = y;
	serviceTime = servTime;
	
}

ostream& operator<<(ostream& flux, const Customer& customer)
{
    flux << "Name: " << customer.customerName <<  endl;
    flux << "Customer number: " << customer.getNumber() << endl;
    /*flux << "X:" << customer.x_coord << " Y:" << customer.y_coord << endl;
    flux << customer.getTemplate() << endl;
    flux << customer.getPenalty() << endl;*/
    return flux;
}


bool Customer::operator==(const Customer& customer2) const
{
    return customerName == customer2.customerName;
}


bool Customer::operator!=(const Customer& customer2) const
{
    return customerName != customer2.customerName;
}



float Customer::getDistance(const Customer& customer2) const {

	return sqrt( (x_coord - customer2.getX())*(x_coord - customer2.getX()) + (y_coord - customer2.getY())*(y_coord - customer2.getY()) ) ;

}

float distance(const Customer& customer1, const Customer& customer2) {
	
	return sqrt ( ( customer1.getX() - customer2.getX())*(customer1.getX() - customer2.getX()) + (customer1.getY() - customer2.getY())*(customer1.getY() - customer2.getY()) );
}

float Customer::getTravelTime(const Customer& customer2) const {

	return this->getDistance(customer2)/AVERAGESPEED ;

}
//float getDistance(const Customer& customer2, const MatriceCarree matAdj) const {}

float travelTime(const Customer& customer1, const Customer& customer2) {
	
	return sqrt ( ( customer1.getX() - customer2.getX())*(customer1.getX() - customer2.getX()) + (customer1.getY() - customer2.getY())*(customer1.getY() - customer2.getY()) ) / AVERAGESPEED;

}

void Customer::setPenaltyFunction(const SettingsGenerator& settings){
	//cout <<"SetPenalty" << endl;	
	PenaltyFunction newFunction(customerTemplateForm, settings);
	penaltyFunction = newFunction;
}




/* CustomerGenerator */

CustomerGenerator::CustomerGenerator(const string& customersFile, const string& preferencesFile, char numberOfCustomersC) {

	int number = (int) (numberOfCustomersC);
	ofstream customers(customersFile);
	ofstream preferences(preferencesFile);
	int start;
	int end;
	for (int i = 1; i<= number; i++) {
		customers << i <<"\t"<< rand()%MAXDISTANCE /*x*/ << "\t" << rand()%MAXDISTANCE /*y*/ <<"\t"<< rand()%MAXSERVICE /*service*/<<endl;
		start = rand()%WORKDAY;
		end = rand()%WORKDAY;
		if (start > end) {
			int temp = start;
			start = end;
			end = temp;
			}
		preferences << i <<"\t"<<start<<"\t"<<end<<"\t"<<emphasis[rand()%3]<<"\t"<<preference[rand()%2]<<"\t"<<gradient[rand()%2]<<endl;
	}
}





	

	
	








