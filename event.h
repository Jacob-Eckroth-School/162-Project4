#ifndef EVENT_H
#define EVENT_H
#include "./player.h"

#include <iostream>
using namespace std;



class Event {
	protected:
		char event_type;
		bool is_empty;
	public:
		virtual void encounter(Player&) = 0 ;
		virtual string percept() = 0;	
		char get_event_type();
		void set_event_type(char);
		bool get_is_empty();
		void set_is_empty(bool);

};



#endif
