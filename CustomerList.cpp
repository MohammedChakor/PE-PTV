//CustomerList.cpp

#include "CustomerList.h"

ostream& operator<<(ostream& flux, const CustomerList& customerList) {
	for (int i = 0; i< customerList.getSize(); i++) {
		flux << customerList.getCustomer(i) << "\n";
		}
	return flux;
}

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

	//cout << "Init Templates\n";

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
		//cout << customerNumber << "\t"<< start <<"\t"<< end <<"\t"<< emphasis <<"\t"<< preference <<"\t"<< gradient << endl ;
		//cout << "Flag 2\n";
		if (!flux.eof()) {
			//cout << "Flag 3\n";
			temp[0] = emphasis;
			temp[1] = preference;
			temp[2] = gradient;
			//cout << "Temp: " << temp[0] <<"\t"<< temp[1] <<"\t"<< temp[2] << endl;
			startint = stoi(start);
			endint = stoi(end);			
			//cout << startint <<"\t"<< endint << endl;
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

