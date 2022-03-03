//sommet.cpp

#include <iostream>
#include "Sommet.h"
#include "math.h"
using namespace std;

Sommet::Sommet(const string& nomSommet, float x, float y)
    : nom(nomSommet)
{
    marque = false;
    x_coord = x;
    y_coord = y;
}

ostream& operator<<(ostream& flux, const Sommet& sommet)
{
    flux << sommet.nom << " ";
    flux << "X:" << sommet.x_coord << " Y:" << sommet.y_coord << " ";
    if (sommet.marque)
      flux << "marque";
    else
      flux << "non marque";
    return flux;
}

bool Sommet::operator==(const Sommet& sommet2) const
{
    return nom == sommet2.nom;
}

bool Sommet::operator!=(const Sommet& sommet2) const
{
    return nom != sommet2.nom;
}

float Sommet::distance(const Sommet& sommet2) const {

	return sqrt((x_coord - sommet2.x_coord)*(x_coord - sommet2.x_coord) + (y_coord - sommet2.y_coord)*(y_coord - sommet2.y_coord));
}


