// MatriceCarree.h

#pragma once
#include <vector>
#include "Sommet.h"
using namespace std;

class MatriceCarree
{
public :
    MatriceCarree();
    MatriceCarree(const string& ficMatrice);
    MatriceCarree(const vector<Sommet> sommits); // return adjacency matrix with euclidian distances
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
