// Somme.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

#include "MatriceCarree.h"
#include "Sommet.h"
#include "Client.h"
using namespace std;

#define INFINITY -1

int sommeDelay(string sequence, MatriceCarree* matAdj, vector<int> clientDeliveryTime, int departureTime);
void convertSecondToHour(int time);
vector<Sommet> getSommits(const string& ficSommits);
Sommet getClosestSommit(float client_x, float client_y, vector<Sommet> sommits);

/* A mettre dans un Function.h*/
int tau(vector<Client> sigma, int h, MatriceCarree matAdj);
int function(vector<Client> sigma , int time, int h, MatriceCarree matAdj);
int min_function(vector<Client> sigma, int time, int h, MatriceCarree matAdj);


int main(){
	
	Client c0("0"); //dépot
   	Client c1("1");
   	Client c2("2");
   	Client c3("3");
   	
   	vector<Client> sigma;
   	
   	sigma.push_back(c0);
   	sigma.push_back(c2);
   	sigma.push_back(c1);
   	sigma.push_back(c3);
   	
   	MatriceCarree matAdj("matAdj.txt");
   	
   	cout << "Setup Done \n" ;
   	
   	int test;
   	
   	test = function(sigma, 32400, 3, matAdj);
   	cout << test << "\n"; 		
    


    return 0; 
    
    }
    
    
/*A mettre dans .h */   
int tau(vector<Client> sigma, int h, MatriceCarree matAdj) {
	
	if ( h < 0 || h >= sigma.size()){
		cout << "Index Error //tau \n" ;
		return 0;}
	else {
		return sigma[h].getServiceTime() + matAdj.get(stoi(sigma[h].getName()),stoi(sigma[h+1].getName())) ; 
	}
}

int function(vector<Client> sigma , int time, int h, MatriceCarree matAdj) {

	cout << "Function " << time << " " << h << "\n";

	if (h == 0) {
		if (time < 0) {
			return INFINITY; }
		else {
			return 0; }
		}
	else {
		cout << "Flag Function Return \n";
		return min_function(sigma, time, h, matAdj);
		}
}

int min_function(vector<Client> sigma, int time, int h, MatriceCarree matAdj) {
	
	cout << "min-function " << time << " " << h << "\n";
	int tprim = 0;
	sigma[h].penaltyFunction(tprim) ;
	cout << "Flag 0 \n";
	int min = function(sigma, tprim - tau(sigma, h, matAdj), h-1, matAdj) + sigma[h].getPenalty() ;
	cout << "Flag 1 \n";
	int temp = 0;
	for (int t = 0; t<= time; t++) {
		cout << "Flag 2 \n";
		sigma[h-1].penaltyFunction(t) ;
		temp = function(sigma, t - tau(sigma,h-1,matAdj), h-1, matAdj) + sigma[h-1].getPenalty() ;
		if (temp <= min) {
			min = temp; }
		}
	return min;
}
 
 /* -------------------------------------------- */
   
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

Sommet getClosestSommit(float client_x, float client_y, vector<Sommet> sommits){
	
	Sommet temp("temp", client_x, client_y);
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













