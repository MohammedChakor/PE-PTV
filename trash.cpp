//trash.cpp
int sommeDelay(string sequence, MatriceCarree* matAdj, vector<int> customerDeliveryTime, int departureTime);
void convertSecondToHour(int time);
vector<Sommet> getSommits(const string& ficSommits);
Sommet getClosestSommit(float customer_x, float customer_y, vector<Sommet> sommits);


int tau(vector<Customer> sigma, int h, MatriceCarree matAdj);
int function(vector<Customer> sigma , int time, int h, MatriceCarree matAdj);
int min_function(vector<Customer> sigma, int time, int h, MatriceCarree matAdj);
void switchCustomers(vector<Customer> sigma, int i, int j);
void heuristic(vector<Customer> sigma);


int function(vector<Customer> sigma , int time, int h, MatriceCarree matAdj) {

	//cout << "Function: t= " << time << " " << "Customer: "<< h << "\n";

	if (h == 0) {
		if (time < START) {
			return INFINITY; }
		else {
			return 0; }
		}
	else {
		//cout << "Flag Function Return \n";
		return min_function(sigma, time, h, matAdj);
		}
}

int min_function(vector<Customer> sigma, int time, int h, MatriceCarree matAdj) {
	
	//cout << "min-function " << time << " " << h << "\n";
	int tprim = START;
	sigma[h].penaltyFunction(tprim) ;
	
	int taus = tau(sigma, h-1, matAdj);
	//cout <<"Taus: " << taus << "\n";
	//cout << "*** Flag 0 \n";
	
	int min = function(sigma, tprim - taus, h-1, matAdj) + sigma[h].getPenalty() ;
	//cout << "*** Flag 1 \n";
	int temp = 0;
	for (int t = START; t <= time; t+=300) {
		//cout << "*** Flag 2 \n";
		temp = function(sigma, t - tau(sigma,h-1,matAdj), h-1, matAdj) + sigma[h].getPenalty() ;
		if (temp <= min) {
			min = temp; }
		}
	return min;
}

int tau(vector<Customer> sigma, int h, MatriceCarree matAdj) {
	
	if ( h < 0 || h >= sigma.size()){
		cout << "Index Error //tau \n" ;
		return 0;}
	else {
		//cout << "Fonction tau \n";
		int serviceTime = sigma[h].getServiceTime();
		
		string name1 = sigma[h].getName();
		string name2 = sigma[h+1].getName();
		int index1 = stoi(name1);
		int index2 = stoi(name2);
		int travelTime = matAdj.get(index1, index2);
		int tau = serviceTime + travelTime;
		int tau = sigma[h].getServiceTime() + matAdj.get(stoi(sigma[h].getName()),stoi(sigma[h+1].getName())) ;
		
		//cout << "Tau: " << tau << "\n";
		return  tau;
	}
}

void switchCustomers(vector<Customer> sigma, int i , int j) {
	if (i > sigma.size() || j > sigma.size()) {
		cout << "Index Error \n";
	}
	else{
	
		Customer temp1 = sigma[i];	
		sigma[i] = sigma[j];
		sigma[j] = temp1;
	}
}
 
 
 
 /* -------------------------------------------- */
   
int sommeDelay(string sequence, MatriceCarree* matAdj, vector<int> customerDeliveryTime, int departureTime) {

    int travelTime = departureTime;
    int totalDelay = 0;
    
    int sequenceSize = sequence.length();
    
    int indice_i;
    int indice_j;
         
    
    for (int i=0; i < sequenceSize-1; i++) {
    
        indice_i = sequence[i] - '0';	//conversion en int
        indice_j = sequence[i+1] - '0';        
        travelTime += matAdj->get(indice_i,indice_j); //Travel time between customer i and customer i+1
        
        cout << indice_i << " to " << indice_j << " Travel time: " ; convertSecondToHour(matAdj->get(indice_i,indice_j));
        
        totalDelay += abs(travelTime - customerDeliveryTime[indice_j]);// delay between scheduled delivery time and real delivery time for customer i+1 of the sequence
        
        cout << "Expected delivery time to " << indice_j << ":" ; convertSecondToHour(customerDeliveryTime[indice_j]);
        cout << "Delivery Time: "; convertSecondToHour(travelTime); cout << " Delay: "; convertSecondToHour(abs(travelTime - customerDeliveryTime[indice_j]));
        cout << "Total delay: "; convertSecondToHour(totalDelay);
        }
        
     return totalDelay;

}  

void convertSecondToHour(int time){
	int nbHours = time / 3600 ;
	int nbMinutes = (time % 3600) / 60 ;
	int nbSeconds = (time % 3600) % 60 ;
	
	cout << nbHours << "h" << nbMinutes << "m" << nbSeconds <<"s\n";
}  

vector<Sommet>  getSommits( const string& ficSommits){
	vector<Sommet> verticesList;
	ifstream flux(ficSommits.c_str());
    cout << "Vertices from file to vector \n" ;
    string nom;
    string x;
    string y;
    
    while (!flux.eof()) {
    	//cout << "Flag 1\n" ;
    	flux >> nom >> x >> y;
    	//cout << nom << " "<< x << " " << y << "\n";
    	if (!flux.eof()) {
    			//cout << "Flag 2 \n" ;
                Sommet sommet(nom, stof(x), stof(y));
                //cout << sommet << "sommet\n" ;
                verticesList.push_back(sommet);
                //cout << verticesList.back() << ".back()\n";            
                }
	}
	cout << "Flag 3\n" ;
	
	return verticesList;
}

Sommet getClosestSommit(float customer_x, float customer_y, vector<Sommet> sommits){
	
	Sommet temp("temp", customer_x, customer_y);
	Sommet best("best");
	float distance = temp.distance(sommits[0]);
	for (int i = 1; i < sommits.size(); i++) {
		if (temp.distance(sommits[i]) < distance ) {
			distance = temp.distance(sommits[i]);
			best.setX(sommits[i].getX());
			best.setY(sommits[i].getY());
			best.setNom(sommits[i].getNom());	
			}
		}
	return best;
}


/*void Customer::penaltyFunction( int time){

	if ( time >= start && time <= end ) {
		penalty = 0; }
	else {
		penalty = ALPHA; }
}*/

		/*void setStart (int newStart) { start = newStart; }
		void setEnd (int newEnd) { end = newEnd; }
		void setTimeService (int newTime) { serviceTime = newTime; }		
		void penaltyFunction(int time);*/
		



		/*int getPenalty() const { return penalty; }
		int getServiceTime() const { return serviceTime; }*/
		
		
				//float getTravel(const Customer& customer2, const MatriceCarree matAdj /*distance || travel time matrix */) const ;
				
				
	


	PiecewiseLinearFunction result;
	for (int i = 0; i<pieces.size(); i++) {
		result.addPiece(pieces[i]); }
	for (int i = 0; i<function2.getSize(); i++) {
		result.addPiece(function2.getPiece(i)); }
	return result;	
				
				
void PiecewiseLinearFunction::addPiece(Piece newPiece) {

	cout << *this << endl;
	cout << newPiece << endl;

	cout << "\n******AddPiece()************" << endl;
		int newStart = newPiece.getStart();
		int newEnd = newPiece.getEnd();
		float newGrad = newPiece.getGradient();
		float newConst = newPiece.getConstant();
		
	if (pieces.size() == 0) {
		/*cout <<"Flag 0" << endl;
		cout << newStart <<"\t"<<newEnd<<"\t"<<newGrad<<"\t"<<newConst << endl;	*/
		pieces.push_back(newPiece);
	}
	else {
		/*cout <<"Flag 1" << endl	;	
		cout << newStart <<"\t"<<newEnd<<"\t"<<newGrad<<"\t"<<newConst << endl;
		cout << " Affichage Pieces" << endl;
		cout << pieces[0].getStart() << "\t";
		for (int i = 0; i < pieces.size(); i++) {
			cout << pieces[i].getEnd() << "\t";
			}
		*/
		
		/*If piece is outside the current funcction */
		if (newEnd < pieces[0].getStart()) {
			//cout <<"Flag 2" << endl;
			Piece newPiece0(newEnd,pieces[0].getStart(),0,0,0);
			auto it = pieces.insert(pieces.begin(), newPiece0);
			it = pieces.insert(pieces.begin(), newPiece);			
		}		
		else if (newStart > pieces[pieces.size()-1].getEnd())
		{
			//cout <<"Flag 3" << endl;
			Piece newPiece0(pieces[pieces.size()-1].getEnd(),newStart ,0,0,0);
			pieces.push_back(newPiece0);
			pieces.push_back(newPiece);	
		}
		/**/
		else { /*New piece crosses other pieces */
			//cout <<"General cross" << endl;
			vector<Piece> copy = pieces;
			int indexStart = 0;
			int indexEnd = 1;
			vector<int> points;
			points.push_back(pieces[0].getStart());
						
			/*points*/
			if (pieces.size() > 1) {
			
				//cout << "newStart" << newPiece.getStart() << endl;
				//p0
				if (newPiece.getStart() < pieces[0].getEnd() && newPiece.getStart() > pieces[0].getStart()) {
						//cout <<"Flag 6" << endl;
						points.push_back(newPiece.getStart()); 
						indexStart = points.size() - 1;
						}
				if (newPiece.getEnd() < pieces[0].getEnd() && newPiece.getEnd() > pieces[0].getStart()) {
						//cout <<"Flag 7" << endl;
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						}
				points.push_back(pieces[0].getEnd());				
				
				for (int i = 0; i<pieces.size() -1; i++) { /* ok loop */
					//cout <<"Flag 5" << endl;
					if (newPiece.getStart() < pieces[i+1].getEnd() && newPiece.getStart() > pieces[i].getEnd()) {
						//cout <<"Flag 6" << endl;
						points.push_back(newPiece.getStart()); 
						indexStart = points.size() - 1;
						points.push_back(pieces[i+1].getEnd());
						}
					else if (newPiece.getEnd() < pieces[i+1].getEnd() && newPiece.getEnd() > pieces[i].getEnd()) {
						//cout <<"Flag 7" << endl;
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						points.push_back(pieces[i+1].getEnd());
						}
					else if (i == pieces.size() - 2 && newPiece.getEnd() > pieces[i+1].getEnd()) {
						points.push_back(pieces[i+1].getEnd());
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						}
					else {
						points.push_back(pieces[i+1].getEnd());
					}							 
					//cout <<"Flag 8" << endl;
				}		
			}
			else {
				points.push_back(pieces[0].getEnd());
				if (newPiece.getStart() < pieces[0].getEnd() && newPiece.getStart() > pieces[0].getStart()) {
						//cout <<"Flag 6" << endl;
						int temp = points[points.size()-1];
						//cout << "temp: " << temp << endl;
						//cout << points[points.size()-1];	
						points[points.size()-1] = newPiece.getStart();	
						//cout << points[points.size()-1]	;				
						points.push_back(temp); 
						indexStart = 1;					
						}		
				if (newPiece.getEnd() < pieces[0].getEnd() && newPiece.getEnd() > pieces[0].getStart()) {
						//cout <<"Flag 6" << endl;
						int temp = points[points.size()-1];
						//cout << "temp: " << temp << endl;
						//cout << points[points.size()-1];	
						points[points.size()-1] = newPiece.getEnd();	
						//cout << points[points.size()-1]	;				
						points.push_back(temp); 
						indexEnd = 2;
						}
					//cout <<"Flag 8" << endl;
			}
			
			/*points*/
			
			/*pieces update*/		
			/*cout <<"Flag 9" << endl; 
			cout << "POINTS \t";
			for (int i = 0; i < points.size(); i++) {
				cout << points[i] << "\t"; 
				}*/
			int numberOfPieces = points.size() - 1;	
			//cout << numberOfPieces << endl;
			//cout << pieces.size() << endl;
					
			if ( pieces.size() != numberOfPieces ) {
				int test = numberOfPieces - pieces.size();
				/*cout << "difference of pieces: " << test << endl;
				cout <<"Flag 10" << endl;*/
				for (int i = 0; i < test; i++) {
					//cout << "test" << i << endl;
					Piece temp(0,0,0,0,0);
					pieces.push_back(temp);
				}
				//cout << pieces.size() << endl;
			}
			/*cout <<"Flag 11" << endl;
			cout << "number of pieces: "<< numberOfPieces <<"\t"<< pieces.size() << endl ;	
			for (int i = 0; i < points.size(); i++ ) { cout << points[i] << endl; } */	
			for (int i = 0; i < pieces.size(); i++) {
				pieces[i].setStart(points[i]);
				pieces[i].setEnd(points[i+1]);
				//cout << "pieces[i]: " <<"\t"<< pieces[i].getStart() <<"\t"<< pieces[i].getEnd() << endl;
				}
				
			/*cout << "Pieces update" << endl;
			cout << indexStart << "\t" << indexEnd << endl;*/
			for (int i = 0; i < indexStart; i++ ) {
				//cout << "*1" << endl;
				pieces[i].setGradient(copy[i].getGradient());
				pieces[i].setConstant(copy[i].getConstant());
				pieces[i].setConstPenalty(copy[i].getConstPenalty());
			}
			int offSet = pieces.size() - copy.size();
			/*cout << "offSet" << offSet << endl;
			cout << "copy : " << copy[copy.size() -1] << endl;
			cout << "Start/end" <<"\t"<<indexStart << "\t" << indexEnd << endl;*/
			for (int i = indexEnd; i < pieces.size(); i++) {
				//cout << "*2" << endl;
				pieces[i].setGradient(copy[i-offSet].getGradient());
				pieces[i].setConstant(copy[i-offSet].getConstant());
				pieces[i].setConstPenalty(copy[i-offSet].getConstPenalty());
			}
			
			for ( int i = indexStart; i < indexEnd; i++ ) {
				//cout << "*3" << endl;
				pieces[i].setGradient(copy[i - offSet + 1].getGradient() + newPiece.getGradient());
				pieces[i].setConstant(copy[i - offSet + 1].getConstant() + newPiece.getConstant());
				pieces[i].setConstPenalty(copy[i - offSet + 1].getConstPenalty() + newPiece.getConstPenalty());				
			}			
			//cout <<"Flag 12" << endl;
			}
		}	
		cout << *this << endl;
}	


	cout << *this << endl;
	cout << newPiece << endl;

	cout << "\n******AddPiece()************" << endl;
		int newStart = newPiece.getStart();
		int newEnd = newPiece.getEnd();
		float newGrad = newPiece.getGradient();
		float newConst = newPiece.getConstant();
		
	if (pieces.size() == 0) {
		/*cout <<"Flag 0" << endl;
		cout << newStart <<"\t"<<newEnd<<"\t"<<newGrad<<"\t"<<newConst << endl;	*/
		pieces.push_back(newPiece);
	}
	else {
		/*cout <<"Flag 1" << endl	;	
		cout << newStart <<"\t"<<newEnd<<"\t"<<newGrad<<"\t"<<newConst << endl;
		cout << " Affichage Pieces" << endl;
		cout << pieces[0].getStart() << "\t";
		for (int i = 0; i < pieces.size(); i++) {
			cout << pieces[i].getEnd() << "\t";
			}
		*/
		
		/*If piece is outside the current funcction */
		if (newEnd < pieces[0].getStart()) {
			//cout <<"Flag 2" << endl;
			Piece newPiece0(newEnd,pieces[0].getStart(),0,0,0);
			auto it = pieces.insert(pieces.begin(), newPiece0);
			it = pieces.insert(pieces.begin(), newPiece);			
		}		
		else if (newStart > pieces[pieces.size()-1].getEnd())
		{
			//cout <<"Flag 3" << endl;
			Piece newPiece0(pieces[pieces.size()-1].getEnd(),newStart ,0,0,0);
			pieces.push_back(newPiece0);
			pieces.push_back(newPiece);	
		}
		/**/
		else { /*New piece crosses other pieces */
			//cout <<"General cross" << endl;
			vector<Piece> copy = pieces;
			int indexStart = 0;
			int indexEnd = 1;
			vector<int> points;
			points.push_back(pieces[0].getStart());
						
			/*points*/
			if (pieces.size() > 1) {
			
				//cout << "newStart" << newPiece.getStart() << endl;
				//p0
				if (newPiece.getStart() < pieces[0].getEnd() && newPiece.getStart() > pieces[0].getStart()) {
						//cout <<"Flag 6" << endl;
						points.push_back(newPiece.getStart()); 
						indexStart = points.size() - 1;
						}
				if (newPiece.getEnd() < pieces[0].getEnd() && newPiece.getEnd() > pieces[0].getStart()) {
						//cout <<"Flag 7" << endl;
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						}
				points.push_back(pieces[0].getEnd());				
				
				for (int i = 0; i<pieces.size() -1; i++) { /* ok loop */
					//cout <<"Flag 5" << endl;
					if (newPiece.getStart() < pieces[i+1].getEnd() && newPiece.getStart() > pieces[i].getEnd()) {
						//cout <<"Flag 6" << endl;
						points.push_back(newPiece.getStart()); 
						indexStart = points.size() - 1;
						points.push_back(pieces[i+1].getEnd());
						}
					else if (newPiece.getEnd() < pieces[i+1].getEnd() && newPiece.getEnd() > pieces[i].getEnd()) {
						//cout <<"Flag 7" << endl;
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						points.push_back(pieces[i+1].getEnd());
						}
					else if (i == pieces.size() - 2 && newPiece.getEnd() > pieces[i+1].getEnd()) {
						points.push_back(pieces[i+1].getEnd());
						points.push_back(newPiece.getEnd()); 
						indexEnd = points.size() - 1;
						}
					else {
						points.push_back(pieces[i+1].getEnd());
					}							 
					//cout <<"Flag 8" << endl;
				}		
			}
			else {
				points.push_back(pieces[0].getEnd());
				if (newPiece.getStart() < pieces[0].getEnd() && newPiece.getStart() > pieces[0].getStart()) {
						//cout <<"Flag 6" << endl;
						int temp = points[points.size()-1];
						//cout << "temp: " << temp << endl;
						//cout << points[points.size()-1];	
						points[points.size()-1] = newPiece.getStart();	
						//cout << points[points.size()-1]	;				
						points.push_back(temp); 
						indexStart = 1;					
						}		
				if (newPiece.getEnd() < pieces[0].getEnd() && newPiece.getEnd() > pieces[0].getStart()) {
						//cout <<"Flag 6" << endl;
						int temp = points[points.size()-1];
						//cout << "temp: " << temp << endl;
						//cout << points[points.size()-1];	
						points[points.size()-1] = newPiece.getEnd();	
						//cout << points[points.size()-1]	;				
						points.push_back(temp); 
						indexEnd = 2;
						}
					//cout <<"Flag 8" << endl;
			}
			
			/*points*/
			
			/*pieces update*/		
			/*cout <<"Flag 9" << endl; 
			cout << "POINTS \t";
			for (int i = 0; i < points.size(); i++) {
				cout << points[i] << "\t"; 
				}*/
			int numberOfPieces = points.size() - 1;	
			//cout << numberOfPieces << endl;
			//cout << pieces.size() << endl;
					
			if ( pieces.size() != numberOfPieces ) {
				int test = numberOfPieces - pieces.size();
				/*cout << "difference of pieces: " << test << endl;
				cout <<"Flag 10" << endl;*/
				for (int i = 0; i < test; i++) {
					//cout << "test" << i << endl;
					Piece temp(0,0,0,0,0);
					pieces.push_back(temp);
				}
				//cout << pieces.size() << endl;
			}
			/*cout <<"Flag 11" << endl;
			cout << "number of pieces: "<< numberOfPieces <<"\t"<< pieces.size() << endl ;	
			for (int i = 0; i < points.size(); i++ ) { cout << points[i] << endl; } */	
			for (int i = 0; i < pieces.size(); i++) {
				pieces[i].setStart(points[i]);
				pieces[i].setEnd(points[i+1]);
				//cout << "pieces[i]: " <<"\t"<< pieces[i].getStart() <<"\t"<< pieces[i].getEnd() << endl;
				}
				
			/*cout << "Pieces update" << endl;
			cout << indexStart << "\t" << indexEnd << endl;*/
			for (int i = 0; i < indexStart; i++ ) {
				//cout << "*1" << endl;
				pieces[i].setGradient(copy[i].getGradient());
				pieces[i].setConstant(copy[i].getConstant());
				pieces[i].setConstPenalty(copy[i].getConstPenalty());
			}
			int offSet = pieces.size() - copy.size();
			/*cout << "offSet" << offSet << endl;
			cout << "copy : " << copy[copy.size() -1] << endl;
			cout << "Start/end" <<"\t"<<indexStart << "\t" << indexEnd << endl;*/
			for (int i = indexEnd; i < pieces.size(); i++) {
				//cout << "*2" << endl;
				pieces[i].setGradient(copy[i-offSet].getGradient());
				pieces[i].setConstant(copy[i-offSet].getConstant());
				pieces[i].setConstPenalty(copy[i-offSet].getConstPenalty());
			}
			
			for ( int i = indexStart; i < indexEnd; i++ ) {
				//cout << "*3" << endl;
				pieces[i].setGradient(copy[i - offSet + 1].getGradient() + newPiece.getGradient());
				pieces[i].setConstant(copy[i - offSet + 1].getConstant() + newPiece.getConstant());
				pieces[i].setConstPenalty(copy[i - offSet + 1].getConstPenalty() + newPiece.getConstPenalty());				
			}			
			//cout <<"Flag 12" << endl;
			}
		}	
		cout << *this << endl;
				
				
				
				
				
				
				
				
				
				
		 
