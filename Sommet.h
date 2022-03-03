//Sommet.h

#pragma once
#include <iostream>
#include <string>
using namespace std;

class Sommet
{
public :
    Sommet(const string& nomSommet, float x = 0, float y = 0);
    string getNom() const             { return nom; }
    bool getMarque() const            { return marque; }
    float getX() const                  { return x_coord;}
    float getY() const                  { return y_coord;}
    
    float distance(const Sommet& sommet2) const;
    
    void setMarque(bool nouvMarque)   { marque = nouvMarque; }
    void setX(float newX)              {x_coord = newX; }
    void setY(float newY)               {y_coord = newY; } 
    void setNom(string nouvNom)  { nom = nouvNom ;}	
    friend ostream& operator<<(ostream& flux, const Sommet& sommet);
    bool operator==(const Sommet& sommet2) const;
    bool operator!=(const Sommet& sommet2) const;
    


private :
    string nom;
    float x_coord;
    float y_coord;
    bool marque;
};
