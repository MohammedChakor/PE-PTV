// Somme.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iterator>
#include <algorithm>
#include <limits>

#include "MatriceCarree.h"
#include "Sommet.h"
using namespace std;

int sommeDelay(string sequence, MatriceCarree* matAdj, vector<int> clientDeliveryTime, int departureTime);
void convertSecondToHour(int time);
vector<Sommet> getSommits(const string& ficSommits);


int main(){

    string sequence = "0123" ;
    //vector<string> permutations;
    
    vector<Sommet> sommits;
    sommits = getSommits("noeuds.txt");
    cout << "test \n" ;
    cout << sommits.front() << " " << sommits.back() << "\n";
    MatriceCarree euclidian(sommits);
    euclidian.afficher(7);

    /*
	MatriceCarree matAdj("matAdj.txt");
	matAdj.afficher(4);
 
    vector<int> clientDeliveryTime;
  	clientDeliveryTime.push_back(0);
  	clientDeliveryTime.push_back(36000);
  	clientDeliveryTime.push_back(40000);
  	clientDeliveryTime.push_back(43000);
  
    int departureTime = 32400;
    convertSecondToHour(departureTime);
    
     
    int delay;
  	delay = sommeDelay(sequence, &matAdj, clientDeliveryTime, departureTime);
    
    cout << "Somme delay:"; convertSecondToHour(delay)  ; */

    return 0; 
    
    }
   
int sommeDelay(string sequence, MatriceCarree* matAdj, vector<int> clientDeliveryTime, int departureTime) {

    int travelTime = departureTime;
    int totalDelay = 0;
    
    int sequenceSize = sequence.length();
    
    int indice_i;
    int indice_j;
         
    
    for (int i=0; i < sequenceSize-1; i++) {
    
        indice_i = sequence[i] - '0';	//conversion en int
        indice_j = sequence[i+1] - '0';        
        travelTime += matAdj->get(indice_i,indice_j); //Travel time between client i and client i+1
        
        cout << indice_i << " to " << indice_j << " Travel time: " ; convertSecondToHour(matAdj->get(indice_i,indice_j));
        
        totalDelay += abs(travelTime - clientDeliveryTime[indice_j]);// delay between scheduled delivery time and real delivery time for client i+1 of the sequence
        
        cout << "Expected delivery time to " << indice_j << ":" ; convertSecondToHour(clientDeliveryTime[indice_j]);
        cout << "Delivery Time: "; convertSecondToHour(travelTime); cout << " Delay: "; convertSecondToHour(abs(travelTime - clientDeliveryTime[indice_j]));
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










