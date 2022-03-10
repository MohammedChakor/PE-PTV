//Client.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "Client.h"
using namespace std;


Client::Client(const string& name, float x, float y, int start, int end, int penalty, int service) {
	
	
	clientName  = name;
	
	x_coord = x;
	y_coord = y;
	
	start = start;
	end = end;
	penalty = penalty;
	serviceTime = service;
	
}

ostream& operator<<(ostream& flux, const Client& client)
{
    flux << client.clientName <<  "\n";
    flux << "X:" << client.x_coord << " Y:" << client.y_coord << "\n";
    return flux;
}


bool Client::operator==(const Client& client2) const
{
    return clientName == client2.clientName;
}


bool Client::operator!=(const Client& client2) const
{
    return clientName != client2.clientName;
}


void Client::penaltyFunction( int time){

	if ( time >= start && time <= end ) {
		penalty = 0; }
	else {
		penalty = ALPHA; }
}






