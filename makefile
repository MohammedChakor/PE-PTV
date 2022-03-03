
MatriceCarree.o : MatriceCarree.h MatriceCarree.cpp
	g++ -c MatriceCarree.cpp

Sommet.o : Sommet.h Sommet.cpp
	g++ -c Sommet.cpp
	
Somme.o : MatriceCarree.h Sommet.h Somme.cpp
	g++ -c Somme.cpp
	   
OBJ = Somme.o Sommet.o MatriceCarree.o
Somme : $(OBJ)
	g++ $(OBJ) -o Somme


	


