#include "./pit.h"
#include "./event.h"
#include "./player.h"
#include <iostream>
using namespace std;
/*********************
 * Function: Pit::Pit()
 * Purpose: Default constructor
 * *******************/
Pit::Pit(){

	event_type = 'p';
	is_empty = false;
}
/*********************
* Function: Pit::encounter(Player&)
* Purpose: Encounters the pit. Nothing happens here, pit handling in main
* *******************/
void Pit::encounter(Player& player){
	

}
/*********************
 * Function: Pit::percept()
 * Purpose: Returns the percept for seeing a pit.
 * *******************/
string Pit::percept(){
	return "You feel a breeze.\n";
}


