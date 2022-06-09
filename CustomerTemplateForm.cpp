//CustomerTemplateForm.cpp

#include <iostream>
#include <string>

#include "CustomerTemplateForm.h"
using namespace std;

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

CustomerTemplateForm::CustomerTemplateForm(const vector<string>& newTemplate, int newStart, int newEnd){

	startTime = newStart;
	endTime = newEnd;
	templateVector = newTemplate;

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


