//PenaltyFunction.cpp
#include "PenaltyFunction.h"

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
			Piece newPiece(filledOutTemplateForm.getStart(), filledOutTemplateForm.getEnd(),gradient,emphasis /*- gradient*filledOutTemplateForm.getStart()*/, settings.get(0,3));
			PiecewiseLinearFunction::insertPiece(newPiece);
			Piece plusInfinity(filledOutTemplateForm.getEnd(),INFINITY,0,settings.get(0,3),settings.get(0,3));
			PiecewiseLinearFunction::insertPiece(plusInfinity);
}


