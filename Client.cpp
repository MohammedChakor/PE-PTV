//Client.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "Client.h"
using namespace std;


Client::Client(const string& name, float x, float y, HAPPINESS happiness) {
	
	//cout << "Number of steps: " << NUMBEROFSTEPS << "\n";
	clientName  = name;
	clientHappiness = happiness;
	x_coord = x;
	y_coord = y;
	
	for (int i = 0; i< NUMBEROFSTEPS; i++) {
		timeWindow[i] = VERYHIGH; 
		}	
}

ostream& operator<<(ostream& flux, const Client& client)
{
    flux << client.clientName << " Happiness: " << client.clientHappiness << "\n";
    flux << "X:" << client.x_coord << " Y:" << client.y_coord << "\n";
    cout << client.timeWindow[0] << " " << client.timeWindow[1] << "\n";

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

HAPPINESS Client::getTimeWindowHappiness(int index) {
	if (index < NUMBEROFSTEPS )	{
		return timeWindow[index];
		}
	else {
		cout << "Index error, CANCEL used instead \n";
		return CANCEL;
	}
}

void Client::displayTimeWindow() const {
	
	for (int i=0; i < NUMBEROFSTEPS; i++ ) {
		cout << timeWindow[i] << " "; }
	cout << "\n";
} 

void Client::hardWindow(int min, int max){

		int index_min = (int) (min - EARLIEST)/STEP;
		int index_max = (int) (max - EARLIEST)/STEP;
		cout << "Hard Window : \n" ;
		for (int i = 0; i < index_min; i++) {
			timeWindow[i] = CANCEL; }
		for (int i = index_min; i< index_max; i++) {
			timeWindow[i] = VERYHIGH; }
		for (int i = index_max; i < NUMBEROFSTEPS; i++) {
			timeWindow[i] = CANCEL; }	
		
}






