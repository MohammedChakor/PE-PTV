//Function.cpp 

#include "Function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "Function.h"
#include "Customer.h"

using namespace std;

/* Class Piece */

Piece::Piece(int start, int end, float new_gradient, float new_constant, float constPenalty){
	
		startTime = start;
		endTime = end;
		gradient = new_gradient;
		constant = new_constant;
		constantPenalty = constPenalty;
			
}

float Piece::calculate(int time) const {

	if (time >= startTime && time < endTime) { return gradient*time + constant; }
	else { return constantPenalty ; }
}

float Piece::getMinimum() const {

	if (gradient >= 0) {return gradient*startTime + constant; }
	else { return gradient*(endTime-1) + constant; } // [start; end[  
}
	
bool Piece::operator==(const Piece& piece2) {
	return (startTime == piece2.getStart() && endTime == piece2.getEnd() \
	 && gradient == piece2.getGradient() && constant == piece2.getConstant());
}

bool Piece::operator!=(const Piece& piece2) {
	return (startTime != piece2.getStart() || endTime != piece2.getEnd() \
	 || gradient != piece2.getGradient() || constant != piece2.getConstant());
}

ostream& operator<<(ostream& flux, const Piece& piece) {
	
	flux << piece.getStart() << " " << piece.getEnd() << " " << piece.getGradient() << " " << piece.getConstant() << "\n";
	
	return flux;
}


/*Class PiecewiseLinear Function */

float PiecewiseLinearFunction::calculate(int time) const {

	int size = pieces.size();
	float result = 0;
	
	for (int i = 0; i<size; i++) { 
		result += pieces[i].calculate(time); 
		}
	return result;
}

bool PiecewiseLinearFunction::operator==(const PiecewiseLinearFunction& function2) {

 	if (pieces.size() != function2.getSize()) { return false; }
 	else {
 		for (int i = 0; i < pieces.size(); i++) {
 			if (pieces[i] != function2.getPiece(i)) { return true; }
 		}	
 	}
 	return true;	
}

bool PiecewiseLinearFunction::operator!=(const PiecewiseLinearFunction& function2) {

	return !(*this == function2);
}
	

void PiecewiseLinearFunction::insertPiece(Piece& newPiece) {

	int i = getIndexStart(newPiece.getStart()); /* returns the correct index to insert the piece in time order */
	auto it = pieces.begin();
	if (i != -1) {
		auto it = pieces.insert(pieces.begin() + i, newPiece);
		 /* vector::insert inserts the piece before the vectorvalue given by the index */
	}
	else{
		pieces.push_back(newPiece); /*start time is bigger than all the other start times, we push it at the end */
	}
	correctOverlap();	
}

void PiecewiseLinearFunction::addPiece(Piece newPiece) {

}	

ostream& operator<<(ostream& flux, const PiecewiseLinearFunction& pwlf){

	int size = pwlf.getSize();
	for (int i = 0; i<size; i++) {
		flux << pwlf.getPiece(i) << "\n"; }
	return flux;
}

PiecewiseLinearFunction PiecewiseLinearFunction::operator+(const PiecewiseLinearFunction& function2) const {
	
	vector<Piece> somme;
	int i = 0;
	int j= 0;
	int stop = 0;
	Piece newPiece;
	while ( stop == 0) {	
		if (pieces[i].getEnd() < function2.getPiece(j).getEnd() && i < pieces.size()){
			newPiece.setStart(pieces[i].getStart());
			newPiece.setEnd(pieces[i].getEnd());
			newPiece.setGradient(pieces[i].getGradient() + function2.getPiece(j).getGradient());
			newPiece.setConstant(pieces[i].getConstant() + function2.getPiece(j).getConstant());
			somme.push_back(newPiece);
			i++;
			}
		else if (function2.getPiece(j).getEnd() < pieces[i].getEnd()  && j < function2.getSize()) {
			newPiece.setStart(function2.getPiece(j).getStart());
			newPiece.setEnd(function2.getPiece(j).getEnd());
			newPiece.setGradient(pieces[i].getGradient() + function2.getPiece(j).getGradient());
			newPiece.setConstant(pieces[i].getConstant() + function2.getPiece(j).getConstant());
			somme.push_back(newPiece);
			j++;		
		}
		else {
			newPiece.setStart(somme[somme.size() - 1].getEnd());
			newPiece.setEnd(INFINITY);
			newPiece.setGradient(pieces[i].getGradient() + function2.getPiece(j).getGradient());
			newPiece.setConstant(pieces[i].getConstant() + function2.getPiece(j).getConstant());
			somme.push_back(newPiece);
			for (int i = 1; i < somme.size(); i++) {
				somme[i].setStart(somme[i-1].getEnd());
				}			
			stop = 1;			
		}
	}	
	PiecewiseLinearFunction result(somme);
	return result;
}

PiecewiseLinearFunction PiecewiseLinearFunction::min() const {

	/* Find each pieces' minimum and reset the pieces' parameter to a constant function = to the minimum */

	PiecewiseLinearFunction newFunction;
	Piece temp;
	cout << "Min" << endl;
	float min = pieces[0].calculate(pieces[0].getStart());

	
	for (int i = 0; i < pieces.size(); i++ ) {	
		if (pieces[i].calculateEnd() < min && pieces[i].calculate(pieces[i].getStart()) > min) {
			int newPoint = (int) (min - pieces[i].getConstant())/pieces[i].getGradient();
			newFunction.setEndPiece(i-1, newPoint);
			temp = pieces[i];
			temp.setStart(newPoint);
			newFunction.insertPiece(temp);
			min = pieces[i].calculateEnd();
		}
		else if (pieces[i].calculateEnd() <= min) { /* keep the piece */
			temp = pieces[i];
			newFunction.insertPiece(temp);
			min = pieces[i].calculateEnd();
		}
		else {
			temp = pieces[i];
			temp.setGradient(0);
			temp.setConstant(min);
			newFunction.insertPiece(temp);
			}
		cout << min << endl;
		}
	return newFunction;
}

PiecewiseLinearFunction PiecewiseLinearFunction::offSet(int offSet) const { 
	cout << "Offset" << endl;
	PiecewiseLinearFunction newFunction = *this;
	cout << newFunction << endl; 
	for (int i = 0; i < pieces.size(); i++) {
		newFunction.setStartPiece(i, pieces[i].getStart() + offSet);
		newFunction.setEndPiece(i, pieces[i].getEnd() + offSet);
		}
	return newFunction;			
}
		

/* Penalty function */

PenaltyFunction::PenaltyFunction(const CustomerTemplateForm& filledOutTemplateForm, const SettingsGenerator& settings) {
	//cout <<"Penalty Function"<<endl;
	int emphasis; /* {"very_much||much||rather", "like||dislike", "sooner||later"}*/
	int gradient;
	//cout << "verif tempalte vector: "<< filledOutTemplateForm.get(0) << "\t" << filledOutTemplateForm.get(1) << "\t" << filledOutTemplateForm.get(2) << endl;
	if (filledOutTemplateForm.get(0)=="very_much"){
			//cout <<"verymuch"<< endl;		
			if (filledOutTemplateForm.get(1) == "like") {
				//cout << "like" << endl;
				emphasis = settings.get(0,0); 
				}
			else{
				//cout << "dislike" << endl;
				emphasis = settings.get(1,0); 
				}
				
			if (filledOutTemplateForm.get(1) == "like" && filledOutTemplateForm.get(2) == "sooner" || filledOutTemplateForm.get(1) == "dislike" && filledOutTemplateForm.get(2) == "later") {
				//cout << "likesooner" << endl;
				gradient = settings.get(2,0); 
				}
			else{
				//cout << "likelater" << endl;
				gradient = settings.get(3,0); 
				}
	}
			
	else if (filledOutTemplateForm.get(0)=="much") {
			//cout << "much" << endl;
			if (filledOutTemplateForm.get(1) == "like") {
				//cout << "like" << endl;
					emphasis = settings.get(0,1); 
					}
			else{
					//cout << "dislike" << endl;
					emphasis = settings.get(1,1); 
					}
			if (filledOutTemplateForm.get(1) == "like" && filledOutTemplateForm.get(2) == "sooner" || filledOutTemplateForm.get(1) == "dislike" && filledOutTemplateForm.get(2) == "later") {
					//cout << "likesooner" << endl;
					gradient = settings.get(2,1); 
					}
			else{
					//cout << "likelater" << endl;
					gradient = settings.get(3,1); 
					}
	}
	else if (filledOutTemplateForm.get(0)=="rather")	{
			//cout << "rather" << endl;	
			if (filledOutTemplateForm.get(1) == "like") {
				emphasis = settings.get(0,2); 
				}
			else{
				emphasis = settings.get(1,2); 
				}
			if (filledOutTemplateForm.get(1) == "like" && filledOutTemplateForm.get(2) == "sooner" || filledOutTemplateForm.get(1) == "dislike" && filledOutTemplateForm.get(2) == "later") {
				gradient = settings.get(2,2); 
				}
			else{
				gradient = settings.get(3,2); 
				}
	}
	else {
		cout << "Template error" << endl;

			}
			Piece minusInfinity(-INFINITY,filledOutTemplateForm.getStart(),0,settings.get(0,3),settings.get(0,3));
			PiecewiseLinearFunction::insertPiece(minusInfinity);
			Piece newPiece(filledOutTemplateForm.getStart(), filledOutTemplateForm.getEnd(),gradient,emphasis, settings.get(0,3));
			PiecewiseLinearFunction::insertPiece(newPiece);
			Piece plusInfinity(filledOutTemplateForm.getEnd(),INFINITY,0,settings.get(0,3),settings.get(0,3));
			PiecewiseLinearFunction::insertPiece(plusInfinity);
}

/* Class Tour */

Tour::Tour() {

	/*Adds warehouse in first position */
	Customer warehouse("WAREHOUSE",0,0,0,0);
	addCustomer(warehouse);
}

PiecewiseLinearFunction Tour::propagatedFunction(int h) const {

	/* f0 definition */
	cout << "fO def : " << endl;
	PiecewiseLinearFunction f0;
	Piece minusInfinity(-INFINITY,0,0,INFINITY,0);
	Piece plusInfinity(0,INFINITY,0,0,0);
	f0.insertPiece(minusInfinity);
	f0.insertPiece(plusInfinity);
	cout << "End of fO def  " << f0 << endl;
	
	if (h == 0) {
		return f0; }
	else {
		return (propagatedFunction(h-1).offSet(/*tau*/ getCustomer(h-1).getServiceTime() + getCustomer(h-1).getTravelTime(getCustomer(h)) /*tau*/) + getCustomer(h).getPenalty()).min() ;
		}
}













	
