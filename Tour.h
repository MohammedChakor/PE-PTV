//Tour.h

#pragma once
#include "CustomerList.h"
using namespace std;

class Tour : public CustomerList {
	
	public :
	
		Tour();
		Tour(const CustomerList& customers);
		void switchCustomers(int i, int j, int k);
		void reverse(int start, int end);
		float getDistance();
		float getTravelTime();
				
		void addWarehouse();
		void removeWarehouse();
		PiecewiseLinearFunction propagatedFunction(int h) const; //défintion de tau(h) à revoir
		PiecewiseLinearFunction ibarakiFunction(int h);
		float evaluate(const PiecewiseLinearFunction ibarakiFunction) const;
		int getSize() const { return CustomerList::getSize(); }
	
	private :
		 

};
