//Client.h

#pragma once
#include <iostream>
#include <string>
using namespace std;

enum HAPPINESS {CANCEL, VERYLOW, LOW, MEDIUM, HIGH, VERYHIGH }; 
#define STEP 0.5 // time step for time window, here 30 minutes (0.5 hours)
#define EARLIEST 8 // time for earliest deliveries, here 8AM
#define LATEST 18 // time for latest deliveries, here 6PM
#define NUMBEROFSTEPS (int) ((LATEST - EARLIEST)/STEP)

class Client
{
	public :
	
		//Client();
		Client(const string& name, float x = 0, float y = 0, HAPPINESS happiness = VERYHIGH);

		string getName() const { return clientName; }
		float getX() const { return x_coord; }
		float getY() const { return y_coord; }
		HAPPINESS getHappiness() const { return clientHappiness; }
		HAPPINESS getTimeWindowHappiness(int index ); 

		void setName(const string& newName) { clientName = newName; }
		void setX(float newX) { x_coord = newX; }
		void setY(float newY) { y_coord = newY; }
		
		void displayTimeWindow() const;
		
		/* Satisfaction patrons */
		void hardWindow(int min, int max);
	
		friend ostream& operator<<(ostream& flux, const Client& client);
		bool operator==(const Client& client2) const;
		bool operator!=(const Client& client2) const;	 
		
	private :
		
		string clientName;
		float x_coord;
		float y_coord;
		
		HAPPINESS clientHappiness;	
		
		HAPPINESS timeWindow[NUMBEROFSTEPS]; 
		
};
