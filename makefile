
MatriceCarree.o : MatriceCarree.h MatriceCarree.cpp
	g++ -c MatriceCarree.cpp

CustomerTemplateForm.o : CustomerTemplateForm.h CustomerTemplateForm.cpp
	g++ -c CustomerTemplateForm.cpp
	
SettingsGenerator.o : SettingsGenerator.h SettingsGenerator.cpp
	g++ -c SettingsGenerator.cpp
	
Piece.o : Piece.h Piece.cpp
	g++ -c Piece.cpp
	
PiecewiseLinearFunction.o : PiecewiseLinearFunction.h PiecewiseLinearFunction.cpp
	g++ -c PiecewiseLinearFunction.cpp
	
PenaltyFunction.o : PenaltyFunction.h PenaltyFunction.cpp
	g++ -c PenaltyFunction.cpp
	
Customer.o : Customer.h Customer.cpp
	g++ -c Customer.cpp
	
CustomerList.o : CustomerList.h CustomerList.cpp
	g++ -c CustomerList.cpp

Tour.o : Tour.h Tour.cpp
	g++ -c Tour.cpp
	
Tsp.o : Tsp.h Tsp.cpp
	g++ -c Tsp.cpp
	
Somme.o : MatriceCarree.h Customer.h Function.h CustomerTemplateForm.h SettingsGenerator.h Piece.h PiecewiseLinearFunction.h PenaltyFunction.h CustomerList.h Tour.h Tsp.h
	g++ -c Somme.cpp
	   
OBJ = Somme.o MatriceCarree.o Customer.o CustomerTemplateForm.o SettingsGenerator.o Piece.o PiecewiseLinearFunction.o PenaltyFunction.o CustomerList.o Tour.o Tsp.o

Somme : $(OBJ)
	g++ $(OBJ) -o Somme


	


