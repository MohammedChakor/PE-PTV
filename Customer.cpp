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

void Customer::setPenaltyFunction(const SettingsGenerator& settings){
	cout <<"SetPenalty" << endl;	
	PenaltyFunction newFunction(customerTemplateForm, settings);
	penaltyFunction = newFunction;
}

ostream& operator<<(ostream& flux, const CustomerList& customerList) {
	for (int i = 0; i< customerList.getSize(); i++) {
		flux << customerList.getCustomer(i) << "\n";
		}
	return flux;
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
		flux << temp <<  "\t"; }  
		
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
	string customerNumber;
	string start;
	string end;
	string emphasis;
	string preference;
	string gradient;
	int startint;
	int endint;
	vector<string> temp;
	CustomerTemplateForm newTemplate;
	for (int i =0; i<3; i++) { temp.push_back("");}
	//cout << "Flag 1\n";
	while (!flux.eof()) {
		flux >> customerNumber >> start >> end >> emphasis >> preference >> gradient ; /*use of intermediate strings to facilitate the understanding of the code, could have directly used temp[0] temp[1] etc */
		cout << customerNumber << "\t"<< start <<"\t"<< end <<"\t"<< emphasis <<"\t"<< preference <<"\t"<< gradient << endl ;
		//cout << "Flag 2\n";
		if (!flux.eof()) {
			//cout << "Flag 3\n";
			temp[0] = emphasis;
			temp[1] = preference;
			temp[2] = gradient;
			cout << "Temp: " << temp[0] <<"\t"<< temp[1] <<"\t"<< temp[2] << endl;
			startint = stoi(start);
			endint = stoi(end);			
			cout << startint <<"\t"<< endint << endl;
			newTemplate.setVector(temp);
			newTemplate.setStart(startint);
			newTemplate.setEnd(endint);
			
			int index = getIndex(stoi(customerNumber));
			
			//cout << "Flag 4\n";
			if (index != -1) {
				//cout << "Flag 5\n";
				customerList[index].setTemplate(newTemplate);
				//cout << "Flag 6\n";
				}
			}
		}
		cout << "Template init done" << endl;
}

void CustomerList::initPenalties(const SettingsGenerator& settings){
	cout << "Penalties init" << endl;
	for (int i =0; i<customerList.size(); i++) {
		//cout <<"Flag 0"<< endl;
		customerList[i].setPenaltyFunction(settings); }
}


/* CustomerGenerator */

CustomerGenerator::CustomerGenerator(const string& customersFile, const string& preferencesFile, int numberOfCustomers) {

	ofstream customers(customersFile);
	ofstream preferences(preferencesFile);
	srand (time(NULL));
	int start;
	int end;
	for (int i = 1; i<= numberOfCustomers; i++) {
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

/*Setting Generator */

SettingsGenerator::SettingsGenerator() : settingsMatrix(4){ /*generates a .txt file with a format that can be used in the Matrix() constructor */

	string settingsFile;
	cout <<"Name of new settings file (name.txt) :\n";
	cin >> settingsFile;
	int temp1;
	int temp2;
	int temp3;
	int dis;
	int addis;
	int trash = 0;
	ofstream settings(settingsFile);
	cout << "Settings initialization in " << settingsFile << " for penalty function generation: \n";
	
	settings << 4 << endl; /*Matrix dimension 4x4 */
	
	cout << "Dissatisfaction value for every second of travel time: ";
	cin >> dis;	
	
	cout << "Additional dissatisfaction value when working overtime: ";
	cin >> addis;	
	
	cout << "Mapping each of „very much“, „much“ and „rather“ to an EMPHASIS value in case of „LIKE“, enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< dis << endl;
	settingsMatrix.set(0,0,temp1);
	settingsMatrix.set(0,1,temp2);
	settingsMatrix.set(0,2,temp3);
	settingsMatrix.set(0,3,dis);
	
	cout << "Mapping each of „very much“, „much“ and „rather“ to an EMPHASIS value in case of „DISLIKE“, enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< addis << endl;
	settingsMatrix.set(1,0,temp1);
	settingsMatrix.set(1,1,temp2);
	settingsMatrix.set(1,2,temp3);
	settingsMatrix.set(1,3,addis);
	
	cout << "Mapping each of „very much“, „much“ and „ratclearher“ to a GRADIENT value in case of („sooner“ and „like“) or („LATER“ and „dislike“), enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< trash << endl;
	settingsMatrix.set(2,0,temp1);
	settingsMatrix.set(2,1,temp2);
	settingsMatrix.set(2,2,temp3);
	
	cout << "Mapping each of „very much“, „much“ and „rather“ to a GRADIENT value in case of („later“ and „like“) or („SOONER“ and „dislike“), enter 3 values: ";
	cin >> temp1 >> temp2 >> temp3;
	settings << temp1 <<"\t"<< temp2 <<"\t"<< temp3 <<"\t"<< trash << endl;
	settingsMatrix.set(3,0,temp1);
	settingsMatrix.set(3,1,temp2);
	settingsMatrix.set(3,2,temp3);
}


SettingsGenerator::SettingsGenerator(const string& settingsFile) : settingsMatrix(settingsFile, "momolebg"){}



	

	
	








