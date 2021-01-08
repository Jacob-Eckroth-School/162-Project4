#include "./game.h"
#include "./room.h"
#include "./wumpus.h"
#include "./pit.h"
#include "./gold.h"
#include "./bats.h"
#include "./empty.h"
#include "./rope.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
/*************************
 * Function: Game::Game()
 * Purpose: Default Game Constructor.
 * **********************/
Game::Game(){
	width = 4;
	wumpus_dead = false;
	height = 4;
	pits = 2;
	wumpuses = 1;
	bats = 2;
	fill_rooms();
	set_player();
	debug = true;
	game_playing = true;
	firing_arrow = false;
	set_escape_rope();

}
/*************************
 * Function: Game::get_player()
 * Purpose: Returns a reference to the player object
 * **********************/
Player& Game::get_player(){
	return player;
}
/*************************
 * Function: Game::Game(int,int)
 * Purpose: Game constructor that takes in 2 ints for a width and a height. Typically these will be the same number but it should work if they're not
 * **********************/
Game::Game(int x, int y){
	wumpus_dead = false;
	width = x;
	height = y;
	pits = 2;
	wumpuses = 1;
	bats = 2;
	fill_rooms();
	set_player();
	debug = false; //automatic for this simple game constructpr
	game_playing = true;
	firing_arrow = false;
	set_escape_rope();

}
/*************************
 * Function: Game::Game(int,int,bool)
 * Purpose: Game constructor that takes in 2 ints for width and height, and takes in whether you're in debug mode or not.
 * **********************/
Game::Game(int x, int y, bool debug){
	wumpus_dead = false;
	bats = 2;
	wumpuses = 1;
	pits = 2;
	width = x;
	height = y;
	fill_rooms();
	set_player();
	this->debug = debug;
	game_playing = true;
	firing_arrow = false;
	set_escape_rope();

}
/*************************
 * Function: Game::Game(int,int,bool,int)
 * Purpose: Default Game Constructor that takes in width,height,a bool for debug mode, and the difficulty of the game. Difficulty isn't balance and if the amount of things being placed is greater than the amount of rooms then errors happen. This constructor is mainly for fun.
 * **********************/
Game::Game(int x, int y, bool debug,int difficulty){
	wumpus_dead = false;
	bats = 2*difficulty;
	wumpuses = 1*difficulty;
	pits = 2*difficulty;
	width = x;
	height = y;
	fill_rooms();
	set_player();
	this->debug = debug;
	game_playing = true;
	firing_arrow = false;
	set_escape_rope();
	player.set_arrows(3*difficulty);

}

/*************************
 * Function: Game::play()
 * Purpose: Game loop, that plays the game until it's over.
 * **********************/
void Game::play(){
	do{
		cout<<"\e[2J\n";
		handle_room();	
		print_map();
		if(firing_arrow){
			fire_arrow();
		}
		if(game_playing){
			percept_events();
			player.move(width,height,game_playing,firing_arrow);
		}	
	}while(game_playing);
}


/*************************
 * Function: Game::handle_room()
 * Purpose: Deals with whatever room that the player is currently in.
 * **********************/
void Game::handle_room(){
	bat_move();
	rooms[player.get_x()][player.get_y()].get_event()->encounter(get_player());
	if(player.get_has_gold() && rooms[player.get_x()][player.get_y()].get_event()->get_event_type() == 'g'){
		remove_gold();
	}
	test_if_game_over();
}
/*************************
 * Function: Game::bat_move()
 * Purpose: If the player is on a bat space, move them to a random room that does not have a bat in it.
 * **********************/
void Game::bat_move(){
	if(rooms[player.get_x()][player.get_y()].get_event()->get_event_type() == 'b'){
		rooms[player.get_x()][player.get_y()].get_event()->encounter(get_player());
		do{
			int x = rand() % width;
			int y = rand() % height;
			player.set_x(x);
			player.set_y(y);
		}while(rooms[player.get_x()][player.get_y()].get_event()->get_event_type() == 'b');

	}
}

/*************************
 * Function: Game::test_if_game_over()
 * Purpose: Tests if the game is over, whether the player wins, or whetehr the player is on a wumpus square, or a pit square.
 * **********************/
void Game::test_if_game_over(){
	if(rooms[player.get_x()][player.get_y()].get_event()->get_event_type() == 'r' && player.get_has_gold()){
		game_playing = false;
		cout<<"\033[1;32mYou escaped! Congratulations!\033[0m"<<endl;
	}else if(rooms[player.get_x()][player.get_y()].get_event()->get_event_type() == 'w'){
		cout<<"\033[1;31mYou were eaten by the Wumpus! Better luck next time.\033[0m"<<endl;
		game_playing = false;
	}else if(rooms[player.get_x()][player.get_y()].get_event()->get_event_type() == 'p'){
		cout<<"\033[1;31mOuch! You fell down a pit and died! Better luck next time.\033[0m"<<endl;
		game_playing = false;
	}

}

/*************************
 * Function: Game::remove_gold()
 * Purpose: Removes the gold from whatever room it is in.
 * **********************/
void Game::remove_gold(){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			if(rooms[i][j].get_event()->get_event_type() == 'g'){
				rooms[i][j].set_event(new Empty);
				break;
			}
		}
	}
}

/*************************
 * Function: Game::print_player()
 * Purpose: Prints the player, if the player is gold then print them gold. Else print them white.
 * **********************/
void Game::print_player(){
	if(player.get_has_gold()){
		cout<<"| \033[1;33m*\033[0m ";
	}else{
		cout<<"| * ";
	}

}
/*************************
 * Function: Game::print_map()
 * Purpose: Prints the game map.
 * **********************/
void Game::print_map(){

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			cout<<"+---";
		}
		cout<<"+"<<endl;
		for(int k = 0; k < 3; k++){//prints the 3 lines for each room
			for(int j = 0; j < height; j++){
				if(i == player.get_y() && j == player.get_x() && k == 1){ //if on player space, and in the middle of the sqare
					print_player();	
				}else{
					if(debug && k==1){ //if in debug mode and the middle of the box
						cout<<"| "<<rooms.at(j).at(i).get_event()->get_event_type()<<" ";	
					}else{
						cout<<"|   ";
					}
				}
			}
			cout<<"|";
			cout<<endl;
		}
	}
	for(int j = 0; j < height; j++){
		cout<<"+---";
	}
	cout<<"+"<<endl;
}

/*************************
 * Function: Game::fill_rooms()
 * Purpose: Fills all the rooms in the maze with the objects and the player. 
 * **********************/
void Game::fill_rooms(){

	rooms.resize(width);
	for(int i = 0; i < width; i++){
		rooms.at(i).resize(height);
	}
	place_events();
}



/*************************
 * Function: Game::place_events()
 * Purpose: Places all the random events into the maze. 
 * **********************/
void Game::place_events(){	
	int pits_remaining = pits;
	int bats_remaining = bats;
	int wumpus_remaining = wumpuses;
	int gold_remaining = 1;
	int x;
	int y;
	do{
		x = rand() % width;
		y = rand() % height;
		if (rooms[x][y].get_event()->get_event_type() == ' '){
			if (pits_remaining){
				rooms[x][y].set_event(new Pit);		
				pits_remaining--;
			} else if (bats_remaining){
				rooms[x][y].set_event(new Bats);
				bats_remaining--;	
			} else if (wumpus_remaining){
				rooms[x][y].set_event(new Wumpus);

				wumpus_remaining--;
			} else {
				rooms[x][y].set_event(new Gold);
				gold_remaining--;
			}
		}
	} while(pits_remaining + bats_remaining + wumpus_remaining + gold_remaining != 0);
}
/*************************
 * Function: Game::set_player()
 * Purpose: Places the player into a random empty room
 * **********************/
void Game::set_player(){
	bool player_set = false;
	int x;
	int y;
	do{
		x = rand()%width;
		y = rand()%height;
		if(rooms.at(x).at(y).get_event()->get_event_type() == ' '){
			player.set_x(x);
			player.set_y(y);
			player_set = true;
		}	
	}while(!player_set); //when you make escape rope class, set position to where the player is.

}

/*************************
 * Function: Game::percept_events()
 * Purpose: Percepts all the events in the rooms around the player, error handles if the user is by an edge of the map.
 * **********************/
void Game::percept_events(){
	int player_x = player.get_x(); 
	int player_y = player.get_y();
	cout<<"\033[34m";
	if(player_y -1 >= 0){
		cout<<rooms[player_x][player_y-1];
	}
	if(player_y+1 < height){
		cout<<rooms[player_x][player_y+1];
	}
	if(player_x -1 >=0){
		cout<<rooms[player_x-1][player_y];
	}
	if(player_x + 1 < width){
		cout<<rooms[player_x+1][player_y];
	}
	cout<<"\033[0m";


}
/*************************
 * Function: Game::get_rooms()
 * Purpose: Returns the reference to the 2d vector of rooms.
 * **********************/
vector<vector<Room>>& Game::get_rooms(){
	return rooms;
}
/*************************
 * Function: Game::set_escape_rope()
 * Purpose: Sets the escape rope to whatever space the player is on.
 * **********************/
void Game::set_escape_rope(){
	rooms[player.get_x()][player.get_y()].set_event(new Rope);

}
/*************************
 * Function: Game::fire_arrow()
 * Purpose: Gets input and fires an arrow in that direction.
 * **********************/
void Game::fire_arrow(){
	firing_arrow = false;
	bool valid = false;
	char input;
	cout<<"\nPlease enter wasd to choose the direction you want to fire the arrow:";
	do{

		system("stty raw");
		input = getchar();
		system("stty cooked");
		if(input != 'w' && input != 'a' && input != 's' && input != 'd'){
			cout<<"\nInvalid input. Please enter either w,a,s, or d:";
			valid = false;
		} else {
			valid = true;
		}
		cout<<endl;
	}while(!valid);

	fire_in_direction(input);

}

/*************************
 * Function: Game::kill_wumpus(int,int)
 * Purpose: Kills the wumpus and replaces it with an empty room in the room x,y
 * **********************/
void Game::kill_wumpus(int x, int y){
	cout<<"\033[1;36mYou hear a large thud, and a groan. The wumpus has been slain!\033[0m"<<endl;
	rooms[x][y].set_event(new Empty);
	wumpuses--;
	if(wumpuses == 0){
		wumpus_dead = true;
	}
}
/*************************
 * Function: Game::wumpus_move()
 * Purpose: 75% chance to move the wumpsu to a random empty space that the player is not on.
 * **********************/
void Game::wumpus_move(){
	int wumpus_x = 0;
	int wumpus_y = 0;
	int new_x = 0;
	int new_y = 0;
	bool valid = false;
	int wumpus_moving = rand()%4;
	if(wumpus_moving != 0){
		for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				if(rooms[i][j].get_event()->get_event_type() == 'w' && !(player.get_x() == i && player.get_y() == j)){
					wumpus_x = i;
					wumpus_y = j;
					break;
				}
			}
		}
		do{
			new_x= rand() % width;
			new_y= rand()%height;
			if(rooms[new_x][new_y].get_event()->get_event_type() == ' '){
				valid = true;
			}
		}while(!valid);
		rooms[new_x][new_y].set_event(new Wumpus);
		rooms[wumpus_x][wumpus_y].set_event(new Empty);
		cout<<"\033[1;32mYou hear loud footsteps echoing through the cavern.\033[0m"<<endl;
	}

}
/*************************
 * Function: Game::fire_in_direction(char)
 * Purpose: Fires an arrow in the direction chosen by the user, kills the wumpus if the wumpus is hit.
 * **********************/
void Game::fire_in_direction(char input){
	bool hit = false;

	switch(input){
		case 'w':
			animate_arrow('^');
			for(int i = player.get_y(); i > -1; i--){
				if(rooms[player.get_x()][i].get_event()->get_event_type() == 'w'){
					kill_wumpus(player.get_x(),i);
					hit = true;
				}
			}
			break;
		case 's':
			animate_arrow('v');
			for(int i = player.get_y(); i < height; i++){
				if(rooms[player.get_x()][i].get_event()->get_event_type() == 'w'){
					kill_wumpus(player.get_x(),i);
					hit = true;
				}
			}
			break;
		case 'a':
			animate_arrow('<');
			for(int i = player.get_x(); i > -1; i--){
				if(rooms[i][player.get_y()].get_event()->get_event_type() == 'w'){
					kill_wumpus(i,player.get_y());
					hit = true;
				}
			}
			break;
		case 'd':
			animate_arrow('>');
			for(int i = player.get_x(); i < width; i++){	
				if(rooms[i][player.get_y()].get_event()->get_event_type() == 'w'){
					kill_wumpus(i,player.get_y());
					hit = true;
				}
			}
			break;
		default:
			cout<<"oh no"<<endl;
			break;
	}
	if(!hit && !wumpus_dead){
		wumpus_move();
	}
}
/*************************
 * Function: Game::animate_arrow(int)
 * Purpose: Animates the arrow flying through the maze depending on the direction it's going.
 * **********************/
void Game::animate_arrow(char direction){
	switch(direction){
		case '^':
			for(int i = player.get_y() -1; i >= 0; i--){
				print_map_with_arrow(player.get_x(),i,direction);
				if(rooms[player.get_x()][i].get_event()->get_event_type() == 'w'){
					break;
				}
			}
			break;
		case 'v':
			for(int i = player.get_y() + 1; i < height; i++){
				print_map_with_arrow(player.get_x(),i,direction);
				if(rooms[player.get_x()][i].get_event()->get_event_type() == 'w'){
					break;
				}

			}
			break;
		case '<':
			for(int i = player.get_x() - 1; i >= 0; i--){
				print_map_with_arrow(i,player.get_y(),direction);
				if(rooms[i][player.get_y()].get_event()->get_event_type() == 'w'){
					break;
				}

			}
			break;
		case '>':
			for(int i = player.get_x() + 1; i < width; i++){
				print_map_with_arrow(i,player.get_y(),direction);
				if(rooms[i][player.get_y()].get_event()->get_event_type() == 'w'){
					break;
				}

			}

			break;

	}
	cout<<"\e[2J\n";
	handle_room();
	print_map();

}
/*************************
 * Function: Game::print_map_with_arrow(int,int,char)
 * Purpose: Prints the map, with the arrow char at x,y on the map. Delays at the end for about a second.
 * **********************/
void Game::print_map_with_arrow(int x, int y, char arrow){//kinda long but it has to be, due to the use of the for loops and the variables within those loops.
	cout<<"\e[2J\n";
	handle_room();
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			cout<<"+---";
		}
		cout<<"+"<<endl;
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < height; j++){
				if(i == player.get_y() && j == player.get_x() && k == 1){
					print_player();	
				}else{
					if(i == y && j == x && k ==1){
						if(rooms[j][i].get_event()->get_event_type()=='w'){
							cout<<"| "<<"\033[1;31m"<<arrow<<"\033[0m ";//if it's the wumpus, the arrow turns red.
						}else{
							cout<<"| "<<"\033[1;34m"<<arrow<<"\033[0m ";//blue arrow
						}
					}else if(debug && k ==1){
						cout<<"| "<<rooms.at(j).at(i).get_event()->get_event_type()<<" ";	
					}else{
						cout<<"|   ";
					}
				}
			}
			cout<<"|";
			cout<<endl;
		}
	}
	for(int j = 0; j < height; j++){
		cout<<"+---";
	}
	cout<<"+"<<endl;
	usleep(200000);//about a second
}
