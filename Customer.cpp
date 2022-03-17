//Customer.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
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
    flux << customer.customerName <<  "\n";
    flux << "X:" << customer.x_coord << " Y:" << customer.y_coord << "\n";
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

float Customer::distance(const Customer& customer1, const Customer& customer2) const{
	
	return sqrt ( ( customer1.getX() - customer2.getX())*(customer1.getX() - customer2.getX()) + (customer1.getY() - customer2.getY())*(customer1.getY() - customer2.getY()) );
}

float Customer::getTravelTime(const Customer& customer2) const {

	return this->getDistance(customer2)/AVERAGESPEED ;

}
//float getDistance(const Customer& customer2, const MatriceCarree matAdj) const {}

float Customer::travelTime(const Customer& customer1, const Customer& customer2) const{
	
	return sqrt ( ( customer1.getX() - customer2.getX())*(customer1.getX() - customer2.getX()) + (customer1.getY() - customer2.getY())*(customer1.getY() - customer2.getY()) ) / AVERAGESPEED;

}

/* CustomerTemplateForm */

CustomerTemplateForm::CustomerTemplateForm() {

	/*

	string temp;
	int start;
	int end;
	
	cout << "I would {very much, much, rather}{like, dislike} to be served {before,after} {time} / between {time} and {time}, the {sooner, later} the better \\n" ;
	
	cout << "Fill the sentence following the template: \n";
	
	cout << "I would {very much, much, rather} ";
	cin >> temp;
	templateVector.push_back(temp);
	cout << "{like, dislike} ";
	cin >> temp;
	templateVector.push_back(temp);
	cout << "to be served {before,after} ";
	cin >> temp;
	templateVector.push_back(temp);
	cout << "{time}";
	cin >> temp;
	templateVector.push_back(temp);
	cout << "between {time}";
	cin >> start;
	startTime = start;
	cout << "and {time}";
	cin >> end;
	endTime = end;
	cout << "the {sooner, later}";
	cin >> temp;
	templateVector.push_back(temp);
	cout << "the better \n";
	
	*/
	
}

ostream& operator<<(ostream& flux, const CustomerTemplateForm& ctf)
{
	int temp;
	temp = ctf.getSize();
	for (int i = 0; i< temp; i++) {
	string temp = ctf.get(i);
		flux << temp <<  "\n"; }  
		
	flux << "Start: " << ctf.getStart()<< " Endtime: " << ctf.getEnd() << "\n";
	   
    return flux;
}

CustomerTemplateForm::CustomerTemplateForm(const vector<string>& newTemplate, int newStart, int newEnd){

	startTime = newStart;
	endTime = newEnd;
	templateVector = newTemplate;

}


/*CustomerList*/

CustomerList::CustomerList(const string& customersFile) {
	
	ifstream flux(customersFile.c_str());
	Customer temp;
	int number;
	int x;
	int y;
	int service;
	while (!flux.eof()) {
		flux >> number >> x >> y >> service;
		if (!flux.eof()) {
			Customer temp("test",number,x,y,service);
			customerList.push_back(temp);
			}
		}		
}

void CustomerList::initTemplates(const string& templateFile) {

	cout << "Init Templates\n";

	ifstream flux(templateFile.c_str());
	int customerNumber;
	int start;
	int end;
	string emphasis;
	string preference;
	string gradient;
	vector<string> temp;
	for (int i =0; i<3; i++) { temp.push_back("");}
	//cout << "Flag 1\n";
	while (!flux.eof()) {
		flux >> customerNumber >> start >> end >> emphasis >> preference >> gradient ; /*use of intermediate strings to facilitate the understanding of the code, could have directly used temp[0] temp[1] etc */
		cout << "Flag 2\n";
		if (!flux.eof()) {
			//cout << "Flag 3\n";
			temp[0] = emphasis;
			temp[1] = preference;
			temp[2] = gradient;
			CustomerTemplateForm newTemplate(temp, start, end);
			int index = getIndex(customerNumber);
			//cout << "Flag 4\n";
			if (index != -1) {
				//cout << "Flag 5\n";
				customerList[index].setTemplate(newTemplate);
				//cout << "Flag 6\n";
				}
			}
		}
}

ostream& operator<<(ostream& flux, const CustomerList& customerList) {
	for (int i = 0; i< customerList.getSize(); i++) {
		flux << customerList.getCustomer(i) << "\n";
		}
	return flux;
}
	

	
	








