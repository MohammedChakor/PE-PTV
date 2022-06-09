//Piece.cpp

#include "Piece.h" 

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

int Piece::argMin() const {
	if (gradient >= 0) {return startTime; }
	else { return endTime; }
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


