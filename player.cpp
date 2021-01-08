#include "./player.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/********************
 * Program: Player::Player()
 * Purpose: Default player constructor, sets amount of arrows to 3
 * *****************/
Player::Player(){
	x = 0;
	y = 0;
	arrows = 3;
	has_gold = false;
}
/********************
 * Program: Player::Player(int,int)
 * Purpose: Player constructor that takes in a x and a y value
 * *****************/
Player::Player(int x, int y){
	this->x = x;
	this->y= y;
	arrows = 3;
	has_gold = false;
}
/********************
 * Program: Player::get_arrows()
 * Purpose: Returns the amount of arrows as an int
 * *****************/
int Player::get_arrows(){
	return arrows;
}
/********************
 * Program: Player::set_arrows(int)
 * Purpose: Updates the amount of arrows to the new int arrows
 * *****************/
void Player::set_arrows(int arrows){
	this->arrows = arrows;
}
/********************
 * Program: Player::get_has_gold()
 * Purpose: Updates the amount of gold the player has
 * *****************/
bool Player::get_has_gold(){
	return has_gold;
}
/********************
 * Program: Player::set_has_gold(bool)
 * Purpose: Updates whether the player has the gold or not with the new bool has_gold
 * *****************/
void Player::set_has_gold(bool has_gold){
	this->has_gold = has_gold;
}
/********************
 * Program: Player::get_x()
 * Purpose: Getter that returns the x value
 * *****************/
int Player::get_x(){
	return x;
}
/********************
 * Program: Player::get_y()
 * Purpose: Getter that returns the y value
 * *****************/
int Player::get_y(){
	return y;
}
/********************
 * Program: Player::set_x(int)
 * Purpose: Updates the value inside the x variable to be the new int x
 * *****************/
void Player::set_x(int x){
	this->x = x;
}
/********************
 * Program: Player::set_y(int)
 * Purpose: Updates the value inside the y variable to be the new int y
 * *****************/
void Player::set_y(int y){
	this->y = y;
}
/********************
 * Program: Player::move(int,int,bool&,bool&)
 * Purpose: Moves the player depending on where they choose, or updates whether they're firing an arrow. Error handles and prevents the player from moving outside of the map.
 * *****************/
void Player::move(int width, int height, bool& gameplaying,bool& firing_arrow){
	cout<<"Use wasd to move, or space bar to fire an arrow. Press q to end the game."<<endl;
	bool valid=false;
	char input;
	do{
		system("stty raw");
		input = getchar();
		system("stty cooked");
		if(input != ' ' && input != 'w' && input != 'a' && input != 's' && input != 'd' && input != 'q'){
			cout<<"\n\033[1;31mInvalid input. Please enter either wasd, space or q:\033[0m";
			valid = false;
		}else{
			valid = true;
		}
		if(input == 'q'){
			gameplaying = false;
		}
	}while(!valid);
	deal_with_move(input,width,height,gameplaying, firing_arrow);
}

/********************
 * Program: Player::cant_move(int,int,bool&,int,bool&)
 * Purpose: Prints that the player can't move and calls the move function again, recursively error handling.
 * *****************/
void Player::cant_move( int width, int height, bool& gameplaying,int direction,bool& firing_arrow){
	string direction_string;
	switch(direction){
		case 0:
			direction_string = "up";
			break;
		case 1:
			direction_string = "down";
			break;
		case 2:
			direction_string = "right";
			break;
		case 3:
			direction_string = "left";
			break;
	}


	cout<<"\033[1;31mYou can't move "<<direction_string<<" anymore. Enter something else.\033[0m"<<endl;
	move(width,height,gameplaying,firing_arrow);
}
/********************
 * Program: Player::deal_with_move(char,int,int,bool&,bool&)
 * Purpose: Deals with the char inputted by the user to move them around the map, and error handles to see if they can actually move. 
 * *****************/
void Player::deal_with_move(char input, int width, int height, bool& gameplaying,bool& firing_arrow){
	switch(input){
		case 'w':
			if(this->y> 0){
				this->y--;
			}else{
				cant_move(width,height,gameplaying,0,firing_arrow);
			}
			break;
		case 's':
			if(this->y< height-1){
				this->y++;
			}else{
				cant_move(width,height,gameplaying,1,firing_arrow);
			}
			break;

		case 'd':
			if(this->x < width - 1){
				this->x++;
			}else{
				cant_move(width,height,gameplaying,2,firing_arrow);
			}
			break;

		case 'a':
			if(this->x > 0){
				this->x--;
			}else{
				cant_move(width,height,gameplaying,3,firing_arrow);
			}
			break;

		case ' ':
			if(arrows > 0){
				fire_arrow(firing_arrow);
				arrows--;
			}else{
				cout<<"\033[1;31mYou don't have any arrows! Choose something else.\033[0m"<<endl;
				move(width,height,gameplaying,firing_arrow);
			}
			break;
	}
}
/********************
 * Program: Player::fire_arrow(bool&)
 * Purpose: Updates the firing arrow status from main to be true, then main can handle the error handling 
 * *****************/
void Player::fire_arrow(bool& firing_arrow){
	firing_arrow = true;
}

