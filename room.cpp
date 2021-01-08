#include "./room.h"
#include "./empty.h"
#include "./wumpus.h"
#include "./pit.h"
#include "./gold.h"
#include "./bats.h"
#include <iostream>
using namespace std;

/******************
 * Function:Room::Room()
 * Purpose: Default room constructor
 * ****************/
Room::Room(){
	Empty* emptyroom = new Empty;
	event = emptyroom;	
}
/******************
 * Function:Room::get_event()
 * Purpose: Returns a pointer to the event in the room class.
 * ****************/
Event* Room::get_event(){
	return event;
}
/******************
 * Function:Room::~Room()
 * Purpose: Default room deconstructor, clears dynamic memory taken from event
 * ****************/
Room::~Room(){
	if(event != NULL){
		delete event;
	}
}
/******************
 * Function:Room::set_event(Event*)
 * Purpose: Updates the eventpointer in event to hold the new event, Event*
  * ****************/
void Room::set_event(Event *newevent){
	if(event != NULL){
		delete event;
	}
	event = newevent;
} 
/******************
 * Function: opearor<<(ostream&,Room&);
 * Purpose: operator overload for printing out a room, calls the percept function when you call to print the room.
  * ****************/
ostream& operator<<(ostream& os, const Room& currentroom){
	
	os<<currentroom.event->percept();
	return os;

}





