//Client.h

#pragma once
#include <iostream>
#include <string>
using namespace std;


#define ALPHA 1200
#define SERVICE 600
#define START 28800
#define END 64800

class Client
{
	public :
		
		Client(const string& name, float x = 0, float y = 0, int start = START, int end = END, int penalty = ALPHA, int service = SERVICE); // start end service in seconds

		string getName() const { return clientName; }
		float getX() const { return x_coord; }
		float getY() const { return y_coord; }
		int getPenalty() const { return penalty; }
		int getStart() const {return start; }
		int getEnd () const { return end; }
		int getServiceTime() const { return serviceTime; }


		void setName(const string& newName) { clientName = newName; }
		void setX(float newX) { x_coord = newX; }
		void setY(float newY) { y_coord = newY; }
		void setStart (int newStart) { start = newStart; }
		void setEnd (int newEnd) { end = newEnd; }
		void setTimeService (int newTime) { serviceTime = newTime; }		
		void penaltyFunction(int time);
	
		friend ostream& operator<<(ostream& flux, const Client& client);
		bool operator==(const Client& client2) const;
		bool operator!=(const Client& client2) const;	 
		
	private :
		
		string clientName;
		int penalty; // 0 ou alhpa
		int start; //wr
		int end;	// wd
		int serviceTime; // u sigma(h)
		float x_coord;
		float y_coord;
		
};
