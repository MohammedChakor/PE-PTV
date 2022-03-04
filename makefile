
MatriceCarree.o : MatriceCarree.h MatriceCarree.cpp
	g++ -c MatriceCarree.cpp

Sommet.o : Sommet.h Sommet.cpp
	g++ -c Sommet.cpp

Client.o : Client.h Client.cpp
	g++ -c Client.cpp

Somme.o : MatriceCarree.h Sommet.h Client.h Somme.cpp 
	g++ -c Somme.cpp
	   
OBJ = Somme.o Sommet.o MatriceCarree.o Client.o
Somme : $(OBJ)
	g++ $(OBJ) -o Somme


	


