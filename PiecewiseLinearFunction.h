//PiecewiseLinearFunction.h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Piece.h"

#pragma once
using namespace std;

#define INFINITY 100000


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
