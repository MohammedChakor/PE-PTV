//Customer.h

#pragma once
#include <iostream>
#include <string>
#include<algorithm>
#include "Function.h"
#include "MatriceCarree.h"
using namespace std;

#define AVERAGESPEED 20 /* m/s */
#define WORKDAY 36000 /*10H*/
#define MAXDISTANCE 50000 /* Perimeter of less than sqrt(2*MAXDISTANCE²) around warehouse */
#define MAXSERVICE 3600 /* max service duration */
#define INFINITY 100000


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

/*Settings */
class SettingsGenerator {
	
	public :
		SettingsGenerator();
		SettingsGenerator(const string& settingsFile);
		int get(int i, int j) const { return settingsMatrix.get(i,j); }
	
	private :
		MatriceCarree settingsMatrix;
};

/* Class Piece */

class Piece {

	public :
		Piece() {}
		Piece(int start, int end, float new_gradient, float new_constant, float constPenalty); // [start; end[  
		void setStart(int newStart) { startTime = newStart; }
		void setEnd (int newEnd ) { endTime = newEnd; }
		void setGradient (float newGrad ) { gradient = newGrad; }
		void setConstant (float newConst) {constant = newConst; }
		void setConstPenalty (float newConst) { constantPenalty = newConst ; }
		
		int getStart() const { return startTime; }
		int getEnd() const { return endTime; }
		float getGradient() const { return gradient; }
		float getConstant() const { return constant; }
		float getConstPenalty() const { return constantPenalty; }
		float getMinimum() const;
		int argMin() const;
		
		float calculate(int time) const;
		float calculateEnd() const { return gradient*endTime + constant; }
		
		friend ostream& operator<<(ostream& flux, const Piece& piece);
		bool operator==(const Piece& piece2);
		bool operator!=(const Piece& piece2);
		
	private : 
		int startTime; // [start; end[
		int endTime;
		float gradient;
		float constant;
		float constantPenalty; /* value outside interval */
};

/*Class PiecewiseLinear Function */

class PiecewiseLinearFunction {
	public :
		PiecewiseLinearFunction() {}
		PiecewiseLinearFunction(const vector<Piece>& newPieces) { pieces = newPieces; }
		
		Piece getPiece(int i) const { return pieces[i] ; }
		
		void setPiece(int i, Piece& newPiece) { pieces[i] = newPiece; }
		void setStartPiece(int i, int newStart) { pieces[i].setStart(newStart); }
		void setEndPiece(int i, int newEnd) { pieces[i].setEnd(newEnd); }
		void insertPiece(Piece& newPiece); /* insert piece in temporal order and correct overlap */
		void addPiece(Piece newPiece);/* used in operator+ where pieces can go on top of each other*/
		
		float calculate(int time) const;
		int getSize() const { return pieces.size(); }
		int argMin() const;
		
		PiecewiseLinearFunction min() const; 
		PiecewiseLinearFunction offSet(int offSet) const; /* returns  f -> f(t-offSet)  pwlf <=> right offset of the function */
		
		friend ostream& operator<<(ostream& flux, const PiecewiseLinearFunction& pwlf);
		bool operator==(const PiecewiseLinearFunction& function2);
		bool operator!=(const PiecewiseLinearFunction& function2);
		PiecewiseLinearFunction operator+(const PiecewiseLinearFunction& function2) const;
		
		
	private :
	
		vector<Piece> pieces;
		void correctOverlap() {
			for (int i = 0; i< pieces.size() - 1; i++) {
				if (pieces[i].getEnd() > pieces[i+1].getStart()) { /* if the intervalls cross */
					pieces[i+1].setStart(pieces[i].getEnd()); /* Avoids collision since pieces are defined in opened interval [start, end[ */
				}
			}
		}
			
		int getIndexStart(int start) const{ /* returns the correct index to insert the piece in time order */
		 	for (int i = 0; i < pieces.size(); i++) {
				if (pieces[i].getStart() > start) {
					return i;
				}
			}
		return -1;	
		}
		
		void cutPieces() { 
			int newIndex;
			for (int i=0; i<pieces.size()-1; i++){
				if (pieces[i].getEnd() > pieces[i+1].getStart() && pieces[i+1].getEnd() > pieces[i].getEnd()) { /* if the intervalls cross */
					Piece newPiece(pieces[i+1].getStart(),pieces[i].getEnd(),pieces[i].getGradient() + pieces[i+1].getGradient(),pieces[i].getConstant() + pieces[i+1].getConstant(), pieces[i+1].getConstPenalty());
					pieces[i].setEnd(newPiece.getStart());
					pieces[i+1].setStart(newPiece.getEnd());
					newIndex = getIndexStart(newPiece.getStart());
					auto it = pieces.insert(pieces.begin() + newIndex,newPiece);
					}
					
				 if ( pieces[i].getEnd() > pieces[i+1].getStart() && pieces[i+1].getEnd() < pieces[i].getEnd()) {
				 	Piece newPiece(pieces[i+1].getEnd(),pieces[i].getEnd(),pieces[i].getGradient(), pieces[i].getConstant(), pieces[i].getConstPenalty());
				 	pieces[i+1].setGradient(pieces[i].getGradient() + pieces[i+1].getGradient());
				 	pieces[i+1].setConstant(pieces[i].getConstant() + pieces[i+1].getConstant());
				 	newIndex = getIndexStart(newPiece.getStart());
				 	auto it = pieces.insert(pieces.begin() + newIndex,newPiece); 		 			 
				 	
				}
			} 
		}						
};



/*Class Penalty Function */
class PenaltyFunction : public PiecewiseLinearFunction {

	public :
		PenaltyFunction() {}
		PenaltyFunction(const CustomerTemplateForm& filledOutTemplateForm, const SettingsGenerator& settings);	
	private :

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
		int getServiceTime() const { return serviceTime; }
		CustomerTemplateForm getTemplate() const { return customerTemplateForm; }
		PenaltyFunction getPenalty() const { return penaltyFunction; }
		
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
		void setPenaltyFunction(const SettingsGenerator& settings);
		void displayPenalty() const { cout << penaltyFunction <<endl; }
		
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
		PenaltyFunction penaltyFunction;	/* generated using the customerTemplateForm */	
};

bool comparatorStart(const Customer& client1, const Customer& client2) {

	return client1.getTemplate().getStart() < client2.getTemplate().getStart();
	
	}
	
bool comparatorEnd(const Customer& client1, const Customer& client2) {

	return client1.getTemplate().getEnd() < client2.getTemplate().getEnd();
	
	}


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
		
		
		void sortStart() { sort(customerList.begin(), customerList.end(), &comparatorStart); }
		void sortEnd() { sort(customerList.begin(), customerList.end(), &comparatorEnd); }
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

/* Generates input files customers et preferences */
class CustomerGenerator {

	public :
		CustomerGenerator(const string& customersFile, const string& preferencesFile, int numerOfCustomers);
	
	private :
		const vector<string> emphasis = {"very_much","much","rather"};
		const vector<string> preference = {"like","dislike"};
		const vector<string> gradient = {"sooner","later"};	
};

class Tour : public CustomerList {
	
	public :
	
		Tour();
		Tour(const CustomerList& customers);
		void switchCustomers(int i, int j, int k);
				
		void addWarehouse();
		void removeWarehouse();
		PiecewiseLinearFunction propagatedFunction(int h) const; //défintion de tau(h) à revoir
		PiecewiseLinearFunction ibarakiFunction(int h);
		float evaluate(const PiecewiseLinearFunction ibarakiFunction) const;
		int getSize() const { return CustomerList::getSize(); }
	
	private :
		 

};

class TSP {

	public :
		TSP(const Tour& tour1) { tour = tour1; } 
		void runTSP();
		Tour getBest() const { return tour; }
		void display() const { cout << tour << endl; } 
		
	private :
	
		Tour tour;

};



















