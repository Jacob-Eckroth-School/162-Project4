#include "./event.h"
#include <iostream>
using namespace std;
/********************
 * Function: Event::get_is_empty()
 * Purpose: Returns whether the event is an empty event or not.
 * *****************/
bool Event::get_is_empty(){
	return is_empty;
}
/********************
 * Function: Event::set_is_empty(bool)
 * Purpose: updates whether an event is empty using the new bool is_empty
 * *****************/
void Event::set_is_empty(bool is_empty){
	this->is_empty = is_empty;
}
/********************
 * Function: Event::get_event_type()
 * Purpose: Returns the type of the event that is currently in the room, as a char. 
 * *****************/
char Event::get_event_type(){
	return event_type;
}
/********************
 * Function: Event::set_event_type(char)
 * Purpose: Updates the event of the room to hold the char newtype instead of the previous event type.
 * *****************/
void Event::set_event_type(char newtype){
	event_type = newtype;
}

