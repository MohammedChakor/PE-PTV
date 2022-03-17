//Function classes

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Customer.h"
using namespace std;

/* Class Piece */

class Piece {

	public :
		Piece();
		Piece(int start, int end, float new_gradient, float new_constant); // [start; end[  
		void setStart(int newStart) { startTime = newStart; }
		void setEnd (int newEnd ) { endTime = newEnd; }
		void setGradient (float newGrad ) { gradient = newGrad; }
		void setConstant (float newConst) {constant = newConst; }
		
		int getStart() const { return startTime; }
		int getEnd() const { return endTime; }
		float getGradient() const { return gradient; }
		float getConstant() const { return constant; }
		float getMinimum() const;
		
		float calculate(int time) const;
		
		friend ostream& operator<<(ostream& flux, const Piece& piece);
		bool operator==(const Piece& piece2);
		bool operator!=(const Piece& piece2);
		
	private : 
		int startTime; // [start; end[
		int endTime;
		float gradient;
		float constant;
};

/*Class PiecewiseLinear Function */

class PiecewiseLinearFunction {

	public :
		PiecewiseLinearFunction() {}
		
		Piece getPiece(int i) const { return pieces[i] ; }
		
		void setPiece(int i, Piece& newPiece) { pieces[i] = newPiece; }
		void insertPiece(Piece& newPiece); /*insert piece in temporal order and correct overlap */
		void addPiece(Piece newPiece) { pieces.push_back(newPiece); } /*used in operator+ where pieces can go on top of each other*/
		
		float calculate(int time) const;
		int getSize() const { return pieces.size(); }
		
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
};


/*Class Penalty Function */
class PenaltyFunction : PiecewiseLinearFunction {

	public :

		//PenaltyFunction(CustomerTemplateForm& filledOutTemplateForm);
	
	private :

};

/*Class Propagated Function */

class PropagatedFunction : PiecewiseLinearFunction {
	
	public :
		
		void propagate(const PropagatedFunction& previousPropagatedFunction /*f_h-1*/, const PenaltyFunction& penaltyFunction /*p_h*/, int additionalTime /*tau*/);
};


















