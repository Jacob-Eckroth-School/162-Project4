#ifndef GOLD_H
#define GOLD_H
#include "./player.h"
#include "./gold.h"
#include "./event.h"
#include "./room.h"
#include <vector>
#include <iostream>
using namespace std;
class Gold: public Event{
	public:
		Gold();
		void encounter(Player&);
		string percept();	
		

};





#endif
