//PiecewiseLinearFunction.cpp

#include "PiecewiseLinearFunction.h"

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
	//cout << "Min" << endl;
	float min = pieces[0].calculate(pieces[0].getStart());

	
	for (int i = 0; i < pieces.size()-1; i++ ) {	
		if (pieces[i].calculateEnd() < min && pieces[i].calculate(pieces[i].getStart()) > min) { /*ok*/
			int newPoint = (int) (min - pieces[i].getConstant())/pieces[i].getGradient();
			newFunction.setEndPiece(i-1, newPoint);
			temp = pieces[i];
			//cout << "temp: " << temp << endl;
			temp.setStart(newPoint);
			newFunction.insertPiece(temp);
			min = pieces[i].calculateEnd();
		}
		else if (pieces[i].calculateEnd() <= min) { 
		/*if gradient < 0 , keep the piece */
			if (pieces[i].getGradient() <= 0) {
				temp = pieces[i];
				newFunction.insertPiece(temp);
				min = pieces[i].calculateEnd();
				}
			else { /* else grad < 0 so min = f(piece.start) */
				temp = pieces[i];
				temp.setGradient(0);
				temp.setConstant(pieces[i].calculate(pieces[i].getStart()));	
				newFunction.insertPiece(temp);		
			}
		}
		else {
			temp = pieces[i];
			temp.setGradient(0);
			temp.setConstant(min);
			newFunction.insertPiece(temp);
			}
		//cout << min << endl;
		}
	return newFunction;
}

PiecewiseLinearFunction PiecewiseLinearFunction::offSet(int offSet) const { 
	//cout << "Offset" << endl;
	PiecewiseLinearFunction newFunction = *this;
	//cout << newFunction << endl; 
	for (int i = 0; i < pieces.size(); i++) {
		newFunction.setStartPiece(i, pieces[i].getStart() + offSet);
		newFunction.setEndPiece(i, pieces[i].getEnd() + offSet);
		}
	return newFunction;			
}

int PiecewiseLinearFunction::argMin() const {
	int min = pieces[0].getMinimum();
	int argMin = pieces[0].argMin();
	for (int i = 0; i < pieces.size(); i++) {
		if (pieces[i].getMinimum	() < min) {
			min = pieces[i].getMinimum();
			argMin = pieces[i].argMin();
			}
	}	
	return argMin;
}
