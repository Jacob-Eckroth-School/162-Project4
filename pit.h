#ifndef PIT_H
#define PIT_H
#include <iostream>
using namespace std;
#include "./player.h"
#include "./event.h"
class Pit : public Event{
	public: 
		Pit();
		void encounter(Player&);
		string percept();	

};




#endif
