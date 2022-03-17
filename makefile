
MatriceCarree.o : MatriceCarree.h MatriceCarree.cpp
	g++ -c MatriceCarree.cpp

Sommet.o : Sommet.h Sommet.cpp
	g++ -c Sommet.cpp

Customer.o : Customer.h Customer.cpp
	g++ -c Customer.cpp

Function.o : Function.h Function.cpp
	g++ -c Function.cpp
	
Somme.o : MatriceCarree.h Sommet.h Customer.h Function.h Somme.cpp 
	g++ -c Somme.cpp
	   
OBJ = Somme.o Sommet.o MatriceCarree.o Customer.o Function.o
Somme : $(OBJ)
	g++ $(OBJ) -o Somme


	


