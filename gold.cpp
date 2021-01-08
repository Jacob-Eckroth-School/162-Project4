#include "./gold.h"
#include "./player.h"

#include <vector>
#include <iostream>
using namespace std;
/*********************
 * Function: Gold::Gold()
 * Purpose: Default constructor
 * *******************/
Gold::Gold(){
	event_type = 'g';
	is_empty = false;
}
/*********************
 * Function: Gold::encounter(Player&)
 * Purpose: Encounter for gold, triggers when user enters room. udpates the player to have the gold.
 * *******************/
void Gold::encounter(Player& player){
	cout<<"\033[1;33mYou got the gold! Now it's time to escape.\033[0m"<<endl;
	player.set_has_gold(true);
}
/*********************
 * Function: Gold::percept()
 * Purpose: Returns the string for the gold perception.
 * *******************/
string Gold::percept(){
	return "You see a glimmer nearby.\n";
}
