//CustomerList
#pragma once
#include "Customer.h"
#include <iostream>
#include <fstream>
using namespace std;


/* Customer list generated using the "customer.csv" file" */
class CustomerList {
	
	public:
		CustomerList() {}
		CustomerList(const string& customersFile);
		void initTemplates(const string& templateFile);
		void initPenalties(const SettingsGenerator& settings); 
		int getSize() const { return customerList.size(); }
		Customer getCustomer(int i) const {return customerList[i]; }
		void setCustomer(int i, const Customer& newCustomer) { customerList[i] = newCustomer; }
		void addCustomer(const Customer& newCust) { customerList.push_back(newCust); }
		void addCustomerStart( const Customer& newCust) { customerList.insert(customerList.begin(), newCust); }
		void removeCustomerStart() { customerList.erase(customerList.begin()) ; }
		void removeCustomerEnd() {customerList.pop_back() ; }
		
		/*bool comparatorStart(const Customer& client1, const Customer& client2) {

			return client1.getTemplate().getStart() < client2.getTemplate().getStart();	
		}
	
		bool comparatorEnd(const Customer& client1, const Customer& client2) {

			return client1.getTemplate().getEnd() < client2.getTemplate().getEnd();
		}					
		
		void sortStart() { sort(customerList.begin(), customerList.end(), comparatorStart); }
		void sortEnd() { sort(customerList.begin(), customerList.end(), comparatorEnd); }*/
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
