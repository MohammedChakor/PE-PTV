//Customer.h

#pragma once
#include <iostream>
#include <string>
#include "Function.h"
#include "MatriceCarree.h"
using namespace std;


#define ALPHA 1200
#define SERVICE 600
#define START 28800
#define END 64800
#define AVERAGESPEED 20


class CustomerTemplateForm {

	public :
		CustomerTemplateForm();
		CustomerTemplateForm(const vector<string>& newTemplate, int newStart, int newEnd);
		
		int getSize() const {return templateVector.size(); }
		string get(int i) const { return templateVector[i] ; }
		int getStart() const {return startTime; }
		int getEnd () const { return endTime; }
		
		friend ostream& operator<<(ostream& flux, const CustomerTemplateForm& ctf);
		
	private :
		int startTime;
		int endTime;
		vector<string> templateVector;	
};


class Customer
{
	public :
		Customer() {}
		Customer(const string& name, int custNumber, float x, float y, int servTime); // start end service in seconds
		string getName() const { return customerName; }
		float getX() const { return x_coord; }
		float getY() const { return y_coord; }
		int getNumber() const {return customerNumber; }
		
		float getDistance(const Customer& customer2) const ;
		float distance(const Customer& customer1, const Customer& customer2) const;
		float getTravelTime(const Customer& customer2) const ;
		float travelTime(const Customer& customer1, const Customer& customer2) const;
		
		void setName(const string& newName) { customerName = newName; }
		void setX(float newX) { x_coord = newX; }
		void setY(float newY) { y_coord = newY; }
		void setNumber(int newN) { customerNumber = newN; }
		void setTemplate(CustomerTemplateForm newTemplate) { customerTemplateForm = newTemplate; }
		void displayTemplate() const { cout << customerTemplateForm << "\n"; }
		
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
		//PenaltyFunction penaltyFunction;	/* generated using the customerTemplateForm */	
};



/* Customer list generated using the "customer.csv" file" */
class CustomerList {
	
	public:
	
		CustomerList(const string& customersFile);
		void initTemplates(const string& templateFile); 
		int getSize() const { return customerList.size(); }
		Customer getCustomer(int i) const {return customerList[i]; }
		friend ostream& operator<<(ostream& flux, const CustomerList& customerList);
		
		
	private :
	
		vector<Customer> customerList;
		int getIndex(int clientNumber) { 
			for (int i = 0; i < customerList.size(); i++) {
				if (customerList[i].getNumber() == clientNumber) {
					return i;
					}
				}
				return -1;
			}
			
};





















