//CustomerTemplateForm.h

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CustomerTemplateForm {

	public :
		CustomerTemplateForm();
		CustomerTemplateForm(const vector<string>& newTemplate, int newStart, int newEnd);
		
		int getSize() const {return templateVector.size(); }
		string get(int i) const { return templateVector[i] ; }
		int getStart() const {return startTime; }
		int getEnd () const { return endTime; }
		
		void setStart(int newStart) {startTime = newStart;}
		void setEnd(int newEnd) { endTime = newEnd; }
		void setVector(const vector<string>& newVector) { templateVector = newVector; }
		
		friend ostream& operator<<(ostream& flux, const CustomerTemplateForm& ctf);
		
	private :
		int startTime;
		int endTime;
		vector<string> templateVector;	/* {"very_much||much||rather", "like||dislike", "sooner||later"}*/
};
