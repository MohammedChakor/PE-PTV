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

Piece::Piece(int start, int end, float new_gradient, float new_constant){
	
		startTime = start;
		endTime = end;
		gradient = new_gradient;
		constant = new_constant;	
}

float Piece::calculate(int time) const {

	if (time >= startTime && time < endTime) { return gradient*time + constant; }
	else { return 0 ; }
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

void PiecewiseLinearFunction::addPiece(Piece newPiece){

	int i = getIndexStart(newPiece.getStart()); /* returns the correct index to insert the piece in time order */
	auto it = pieces.begin();
	if (i != -1) {
		auto it = pieces.insert(pieces.begin() + i, newPiece);
		 /* vector::insert inserts the piece before the vectorvalue given by the index */
	}
	else{
		pieces.push_back(newPiece); /*start time is bigger than all the other start times, we push it at the end */
	}
	cutPieces();
	
}

ostream& operator<<(ostream& flux, const PiecewiseLinearFunction& pwlf){

	int size = pwlf.getSize();
	for (int i = 0; i<size; i++) {
		flux << pwlf.getPiece(i) << "\n"; }
	return flux;
}

PiecewiseLinearFunction PiecewiseLinearFunction::operator+(const PiecewiseLinearFunction& function2) const {
	
	PiecewiseLinearFunction result;
	for (int i = 0; i<pieces.size(); i++) {
		result.addPiece(pieces[i]); }
	for (int i = 0; i<function2.getSize(); i++) {
		result.addPiece(function2.getPiece(i)); }
	
	return result;
}

/* Penalty function */

PenaltyFunction::PenaltyFunction(const CustomerTemplateForm& filledOutTemplateForm, const SettingsGenerator& settings) {
	cout <<"Flag1"<<endl;
	int emphasis; /* {"very_much||much||rather", "like||dislike", "sooner||later"}*/
	int gradient;
	if (filledOutTemplateForm.get(0)=="very_much"){
			cout <<"verymuch"<< endl;		
			if (filledOutTemplateForm.get(1) == "like") {
				cout << "like" << endl;
				emphasis = settings.get(0,0); 
				}
			else{
				cout << "dislike" << endl;
				emphasis = settings.get(0,1); 
				}
				
			if (filledOutTemplateForm.get(1) == "like" && filledOutTemplateForm.get(2) == "sooner" || filledOutTemplateForm.get(1) == "dislike" && filledOutTemplateForm.get(2) == "later") {
				cout << "likesooner" << endl;
				gradient = settings.get(0,2); 
				}
			else{
				cout << "likelater" << endl;
				gradient = settings.get(0,3); 
				}
	}
			
	else if (filledOutTemplateForm.get(0)=="much") {
			cout << "much" << endl;
			if (filledOutTemplateForm.get(1) == "like") {
				cout << "like" << endl;
					emphasis = settings.get(1,0); 
					}
			else{
					cout << "dislike" << endl;
					emphasis = settings.get(1,1); 
					}
			if (filledOutTemplateForm.get(1) == "like" && filledOutTemplateForm.get(2) == "sooner" || filledOutTemplateForm.get(1) == "dislike" && filledOutTemplateForm.get(2) == "later") {
					cout << "likesooner" << endl;
					gradient = settings.get(1,2); 
					}
			else{
					cout << "likelater" << endl;
					gradient = settings.get(1,3); 
					}
	}
	else	{
			cout << "rather" << endl;	
			if (filledOutTemplateForm.get(1) == "like") {
				emphasis = settings.get(2,0); 
				}
			else{
				emphasis = settings.get(2,1); 
				}
			if (filledOutTemplateForm.get(1) == "like" && filledOutTemplateForm.get(2) == "sooner" || filledOutTemplateForm.get(1) == "dislike" && filledOutTemplateForm.get(2) == "later") {
				gradient = settings.get(2,2); 
				}
			else{
				gradient = settings.get(2,3); 
				}
	}
			Piece newPiece(filledOutTemplateForm.getStart(), filledOutTemplateForm.getEnd(),gradient,emphasis);
			PiecewiseLinearFunction::insertPiece(newPiece);

}






	
