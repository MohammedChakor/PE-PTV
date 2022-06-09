//Piece.h
#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
