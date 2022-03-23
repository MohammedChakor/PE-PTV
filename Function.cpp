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

/*
void PiecewiseLinearFunction::addPiece(Piece newPiece){

	int i = getIndexStart(newPiece.getStart()); /* returns the correct index to insert the piece in time order */
	/*auto it = pieces.begin();
	if (i != -1) {
		auto it = pieces.insert(pieces.begin() + i, newPiece);
		 /* vector::insert inserts the piece before the vectorvalue given by the index */
	/*}
	else{
		pieces.push_back(newPiece); /*start time is bigger than all the other start times, we push it at the end */
	/*}
	cutPieces();
	
}*/

void PiecewiseLinearFunction::addPiece(Piece newPiece) {

	cout << "\n******AddPiece()************" << endl;
		int newStart = newPiece.getStart();
		int newEnd = newPiece.getEnd();
		float newGrad = newPiece.getGradient();
		float newConst = newPiece.getConstant();
		
	if (pieces.size() == 0) {
		cout <<"Flag 0" << endl;
		cout << newStart <<"\t"<<newEnd<<"\t"<<newGrad<<"\t"<<newConst << endl;	
		pieces.push_back(newPiece);
	}
	else {
		cout <<"Flag 1" << endl	;	
		cout << newStart <<"\t"<<newEnd<<"\t"<<newGrad<<"\t"<<newConst << endl;
		/**/
		cout << " Affichage Pieces" << endl;
		cout << pieces[0].getStart() << "\t";
		for (int i = 0; i < pieces.size(); i++) {
			cout << pieces[i].getEnd() << "\t";
			}
		/**/
		
		/*If piece is outside the current funcction */
		if (newEnd < pieces[0].getStart()) {
			cout <<"Flag 2" << endl;
			Piece newPiece0(newEnd,pieces[0].getStart(),0,0,0);
			auto it = pieces.insert(pieces.begin(), newPiece0);
			it = pieces.insert(pieces.begin(), newPiece);			
		}		
		else if (newStart > pieces[pieces.size()-1].getEnd())
		{
			cout <<"Flag 3" << endl;
			Piece newPiece0(pieces[pieces.size()-1].getEnd(),newStart ,0,0,0);
			pieces.push_back(newPiece0);
			pieces.push_back(newPiece);	
		}
		/**/
		else { /*New piece crosses other pieces */
			cout <<"General cross" << endl;
			vector<Piece> copy = pieces;
			int indexStart = 0;
			int indexEnd = 1;
			vector<int> points;
			points.push_back(pieces[0].getStart());
						
			/*points*/
			if (pieces.size() > 1) {
				cout << "newStart" << newPiece.getStart() << endl;
				//p0
				if (newPiece.getStart() < pieces[0].getEnd() && newPiece.getStart() > pieces[0].getStart()) {
						cout <<"Flag 6" << endl;
						points.push_back(newPiece.getStart()); 
						indexStart = points.size() - 1;
						}
				if (newPiece.getEnd() < pieces[0].getEnd() && newPiece.getEnd() > pieces[0].getStart()) {
						cout <<"Flag 7" << endl;
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						}
				points.push_back(pieces[0].getEnd());				
				
				for (int i = 0; i<pieces.size() -1; i++) { /* ok loop */
					cout <<"Flag 5" << endl;
					
					if (newPiece.getStart() < pieces[i+1].getEnd() && newPiece.getStart() > pieces[i].getEnd()) {
						cout <<"Flag 6" << endl;
						points.push_back(newPiece.getStart()); 
						indexStart = points.size() - 1;
						points.push_back(pieces[i+1].getEnd());
						}
					if (newPiece.getEnd() < pieces[i+1].getEnd() && newPiece.getEnd() > pieces[i].getEnd()) {
						cout <<"Flag 7" << endl;
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						points.push_back(pieces[i+1].getEnd());
						}
					if (i == pieces.size() - 2 && newPiece.getEnd() > pieces[i+1].getEnd()) {
						points.push_back(pieces[i+1].getEnd());
						points.push_back(newPiece.getEnd()); 
						}
											 
					cout <<"Flag 8" << endl;
					
				}
				
			}
			else {
				points.push_back(pieces[0].getEnd());
				if (newPiece.getStart() < pieces[0].getEnd() && newPiece.getStart() > pieces[0].getStart()) {
						cout <<"Flag 6" << endl;
						int temp = points[points.size()-1];
						cout << "temp: " << temp << endl;
						cout << points[points.size()-1];	
						points[points.size()-1] = newPiece.getStart();	
						cout << points[points.size()-1]	;				
						points.push_back(temp); 
						indexStart = 1;					
						}
				
						
				if (newPiece.getEnd() < pieces[0].getEnd() && newPiece.getEnd() > pieces[0].getStart()) {
						cout <<"Flag 6" << endl;
						int temp = points[points.size()-1];
						cout << "temp: " << temp << endl;
						cout << points[points.size()-1];	
						points[points.size()-1] = newPiece.getEnd();	
						cout << points[points.size()-1]	;				
						points.push_back(temp); 
						indexEnd = 2;
						}
					cout <<"Flag 8" << endl;
	
			}
			
			

			/*points*/
			
			/*pieces update*/		
			cout <<"Flag 9" << endl; 
			cout << "POINTS \t";
			for (int i = 0; i < points.size(); i++) {
				cout << points[i] << "\t"; 
				}
			int numberOfPieces = points.size() - 1;	
			cout << numberOfPieces << endl;
			cout << pieces.size() << endl;
					
			if ( pieces.size() != numberOfPieces ) {
				int test = numberOfPieces - pieces.size();
				cout << "difference of pieces: " << test << endl;
				cout <<"Flag 10" << endl;
				for (int i = 0; i < test; i++) {
					//cout << "test" << i << endl;
					Piece temp(0,0,0,0,0);
					pieces.push_back(temp);
				}
				cout << pieces.size() << endl;
			}
			cout <<"Flag 11" << endl;
			cout << "number of pieces: "<< numberOfPieces <<"\t"<< pieces.size() << endl ;		
			for (int i = 0; i < points.size(); i++ ) { cout << points[i] << endl; }	
			for (int i = 0; i < pieces.size(); i++) {
				pieces[i].setStart(points[i]);
				pieces[i].setEnd(points[i+1]);
				cout << "pieces[i]: " <<"\t"<< pieces[i].getStart() <<"\t"<< pieces[i].getEnd() << endl;
				}
				
			cout << "Pieces update" << endl;
			cout << indexStart << "\t" << indexEnd << endl;
			for (int i = 0; i < indexStart; i++ ) {
				//cout << "*1" << endl;
				pieces[i].setGradient(copy[i].getGradient());
				pieces[i].setConstant(copy[i].getConstant());
				pieces[i].setConstPenalty(copy[i].getConstPenalty());
			}
			int offSet = pieces.size() - copy.size();
			cout << "offSet" << offSet << endl;
			cout << "copy : " << copy[copy.size() -1] << endl;
			cout << "Start/end" <<"\t"<<indexStart << "\t" << indexEnd << endl;
			for (int i = indexEnd; i < pieces.size(); i++) {
				cout << "*2" << endl;
				pieces[i].setGradient(copy[i-offSet].getGradient());
				pieces[i].setConstant(copy[i-offSet].getConstant());
				pieces[i].setConstPenalty(copy[i-offSet].getConstPenalty());
			}
			
			for ( int i = indexStart; i < indexEnd; i++ ) {
				cout << "*3" << endl;
				pieces[i].setGradient(copy[i - offSet + 1].getGradient() + newPiece.getGradient());
				pieces[i].setConstant(copy[i - offSet + 1].getConstant() + newPiece.getConstant());
				pieces[i].setConstPenalty(copy[i - offSet + 1].getConstPenalty() + newPiece.getConstPenalty());				
			}
			
			cout <<"Flag 12" << endl;
			}
		}	
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

PiecewiseLinearFunction PiecewiseLinearFunction::min() const {

	/* Find each pieces' minimum and reset the pieces' parameter to a constant function = to the minimum */

	PiecewiseLinearFunction newFunction;
	Piece piece;
	piece.setGradient(0);
	piece.setConstPenalty(pieces[0].getConstPenalty());
	
	for (int i = 0; i < pieces.size(); i++) {
		piece.setStart(pieces[i].getStart());
		piece.setEnd(pieces[i].getEnd());
		piece.setConstant(pieces[i].getMinimum());
		
		if ( i > 0 &&  piece.getConstant() > newFunction.getPiece(i-1).getConstant()) {
			piece.setConstant(newFunction.getPiece(i-1).getConstant());
			}
		newFunction.addPiece(piece);
		}
	return newFunction;
	
}

PiecewiseLinearFunction PiecewiseLinearFunction::offSet(int offSet) const { 

	PiecewiseLinearFunction newFunction;
	Piece piece;
	piece.setConstPenalty(pieces[0].getConstPenalty());

	for (int i = 0; i < pieces.size(); i++) {
		piece.setStart(pieces[i].getStart() + offSet);
		piece.setEnd(pieces[i].getEnd() + offSet);
		piece.setGradient(pieces[i].getGradient());
		piece.setConstant(pieces[i].getConstant());
		newFunction.addPiece(piece);
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
			Piece newPiece(filledOutTemplateForm.getStart(), filledOutTemplateForm.getEnd(),gradient,emphasis, settings.get(0,3));
			PiecewiseLinearFunction::insertPiece(newPiece);

}

/* Class Tour */

Tour::Tour() {

	/*Adds warehouse in first position */
	Customer warehouse("WAREHOUSE",0,0,0,0);
	addCustomer(warehouse);
}

PiecewiseLinearFunction Tour::propagatedFunction(int h) const {

	/* f0 definition */
	PiecewiseLinearFunction f0;
	Piece minusInfinity(-INFINITY,0,0,INFINITY,0);
	Piece plusInfinity(0,INFINITY,0,0,0);
	f0.addPiece(minusInfinity);
	f0.addPiece(plusInfinity);
	
	if (h == 0) {
		return f0; }
	else {
		return (propagatedFunction(h-1).offSet(/*tau*/ getCustomer(h-1).getServiceTime() + getCustomer(h-1).getTravelTime(getCustomer(h)) /*tau*/) + getCustomer(h).getPenalty()).min() ;
		}
}













	
