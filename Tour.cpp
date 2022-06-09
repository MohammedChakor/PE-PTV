//Tour.cpp

#include "Tour.h"

Tour::Tour() {

	/*Adds warehouse in first position */
	Customer warehouse("WAREHOUSE",0,0,0,0);
	addCustomer(warehouse);
}

Tour::Tour(const CustomerList& customers) {
	
	/*Adds warehouse in first position 
	Customer warehouse("WAREHOUSE",0,0,0,0);
	addCustomer(warehouse);*/
	
	for (int i = 0; i < customers.getSize(); i++) {
		addCustomer(customers.getCustomer(i));
	}
	//addCustomer(warehouse);	
}

void Tour::switchCustomers(int i, int j, int k) {
	
	Customer temp ;
	for (int s = 0; s < k ; s++) {
		temp = getCustomer((i+s)%getSize());
		setCustomer((i+s)%getSize(), getCustomer((j+s) % getSize()));
		setCustomer((j+s) % getSize(), temp);
		
	}	
}

float Tour::getDistance() {

	int size = getSize();
	float dist; 
	for (int i = 0; i < size - 1; i++ ) {
	
		dist += distance(getCustomer(i), getCustomer(i+1));	
	}
	
	return dist;

}

float Tour::getTravelTime() {

	int size = getSize();
	float traveltime; 
	for (int i = 0; i < size - 1; i++ ) {
	
		traveltime += travelTime(getCustomer(i), getCustomer(i+1));	
	}
	
	return traveltime;

}

PiecewiseLinearFunction Tour::propagatedFunction(int h) const {
	
	//cout << *this <<endl;
	PiecewiseLinearFunction f0;
	Piece minusInfinity(-INFINITY,0,0,INFINITY,0);
	Piece plusInfinity(0,INFINITY,0,0,0);
	f0.insertPiece(minusInfinity);
	f0.insertPiece(plusInfinity);
		
	if (h == 0) {
		return f0; }
	else {
		return (propagatedFunction(h-1).offSet(/*tau*/ getCustomer(h-1).getServiceTime() + getCustomer(h-1).getTravelTime(getCustomer(h)) /*tau*/) + getCustomer(h).getPenalty()).min() ;
		}
}

PiecewiseLinearFunction Tour::ibarakiFunction(int h) {

	
	//cout << *this << endl;
	addWarehouse();
	//cout<< *this << endl;
	//cout << getCustomer(h) << endl;
	
	PiecewiseLinearFunction function;
	function = propagatedFunction(h) ;
	removeWarehouse();
	return function;
}

void Tour::addWarehouse() {
	const Customer warehouse("Warehouse",0,0,0,0);
	addCustomerStart(warehouse);
	addCustomer(warehouse);
	}

void Tour::removeWarehouse() {
	if (getCustomer(0).getName() == "Warehouse") {
		removeCustomerStart();
		removeCustomerEnd();
	}
	else {
		cout << "No WArehouse" << endl;
		return;
	}
}


float Tour::evaluate(const PiecewiseLinearFunction ibarakiFunction) const {
	
	return ibarakiFunction.calculate(ibarakiFunction.argMin());

}
