// MatriceCarree.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "MatriceCarree.h"
using namespace std;

MatriceCarree::MatriceCarree()
{
}

MatriceCarree::MatriceCarree(const string& ficMatrice)
{
    ifstream flux(ficMatrice.c_str());
    cout << "Constructeur via fichier texte \n" ;
    int getDim = 0;
    while (!flux.eof()) {
        string i;
        string j;
        string val;
        string dim;
        
        //cout << "Flag 0 \n" ;
        
        if (getDim == 0) {   
            flux >> dim;
            dimension = stoi(dim); 
            cout << "Dimension: " << dimension << "\n";
            vecteur.resize(stoi(dim));
            
            for (int i = 0; i < dimension; i++){
                vecteur[i].assign(dimension, 0);
                } 
            getDim = 1;
            //cout << "Flag 1 \n" ;      
            }
            
        else{
            //cout << "Flag 2 \n" ; 
            flux >> i >> j >> val;
            //cout << i <<" "<< j <<" "<< val << " \n" ;
            if (!flux.eof()) {
                //cout << "Flag 3 \n" ; 
                vecteur[stoi(i)][stoi(j)] = stof(val);            
                }
        }   
        }
}       

MatriceCarree::MatriceCarree(int dim)
{
    dimension = dim;
    vecteur.resize(dim);
    for (int i = 0; i < dim; i++)
        vecteur[i].assign(dim, 0);
}

MatriceCarree::MatriceCarree(const vector<Sommet> sommits) {

	dimension = sommits.size();
	vecteur.resize(sommits.size());
	for (int i = 0; i < sommits.size(); i++){
        vecteur[i].assign(sommits.size(), 0);
        }
        
    for (int i = 0; i < sommits.size(); i++){
    	for (int j = 0; j < sommits.size(); j++){
    		if ( i != j ) {
    			vecteur[i][j] = sommits[i].distance(sommits[j]);
    			}
    		else{
    			vecteur[i][j] = 0;
    			}
    		}
    	}
}

float MatriceCarree::get(int i, int j) const
{
    return vecteur[i][j];
}

void MatriceCarree::set(int i, int j, float val)
{
    vecteur[i][j] = val;
}

void MatriceCarree::redim(int dim)
{
    vecteur.resize(dim);
    for (int i = 0; i < dim; i++)
        vecteur[i].assign(dim, 0);
    dimension = dim;
}

void MatriceCarree::afficher(int taille) const {
    if (taille > dimension) {cout << "erreur dimension\n" ;}
    else {    
        for (int i = 0; i<taille; i++){
            cout << "\n";
            for (int j = 0; j<taille; j++) {
                cout << vecteur[i][j] <<" " ; 
                }
          }
          cout << "\n" ;
     }
}



