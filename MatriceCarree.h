// MatriceCarree.h

#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class MatriceCarree
{
public :
    MatriceCarree();
    MatriceCarree(const string& ficMatrice);            /*graphe format */
    MatriceCarree(const string& ficMatrice, const string& identifer); /* dim + matrix format */
    //MatriceCarree(const vector<Sommet> sommits); // return adjacency matrix with euclidian distances
    MatriceCarree(int dim);
    int getDimension() const    { return vecteur.size(); }
    float get(int i, int j) const;
    void set(int i, int j, float val);
    void redim(int dim);
    void afficher(int taille = 3) const;

private :
    vector< vector<float> > vecteur;
    int dimension;
};
