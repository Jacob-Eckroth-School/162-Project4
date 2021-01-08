/********************************
 * Program: prog.cpp
 * Author: Jacob Eckroth
 * Date: 2/27/20
 * Description: Plays the hunt the wumpus game
 * Input: Takes in 2 commandline arguments, first argument is room size >4, second argument is a bool to indicate whether you're in debug mode or not
 * Output: The game: Hunt the wumpus
 * *****************************/


#include "./game.h"
#include <iostream>
#include <cstdlib>

using namespace std;
void handle_arguments(int argc, char** argv,int& width,  bool& debug);
void validate_size(string&, bool&);
void validate_debug(string&,bool&);
bool play_again();
/********************
 * Program:main(int,char**)
 * Function:Plays the game hunt the wumpus,takes in commandline arguments, and parses them, arg1 being the size of the map, arg2 being true or false for debug mode.
 * *****************/
int main(int argc, char** argv){
	int width = 0;
	bool debug = false;
	handle_arguments(argc,argv,width,debug);
	srand(time(NULL));
	bool still_playing = true;
	do{
		Game game(width,width,debug,1);
		game.play();
		still_playing = play_again();
	}while(still_playing);

	return 0;
}



/********************
 * Program: handle_arguments(int,char**,int&,bool&)
 * Function: Handles all the inputs from the commandline, makes sure they're valid, and updates int width and bool debug to match the inputs.
 * *****************/
void handle_arguments(int argc, char** argv,int& width,bool& debug){
	bool width_valid = false;
	bool debug_valid = false;
	string width_string;
	string debug_string; 
	if(argc != 3){
		cout<<"Incorrect amount of arguments. Please enter the size of the mase, greater or equal to 4:";
		getline(cin,width_string);
		cout<<"Please enter true if you want to operate in debug mode, false otherwise:"<<endl;
		getline(cin,debug_string);
	}else{
		width_string = argv[1];
		debug_string = argv[2];
	}
	validate_size(width_string,width_valid);
	width = stoi(width_string);
	validate_debug(debug_string,debug_valid);	
	(debug_string == "true")?debug = true : debug = false;
}
/********************
 * Program:validate_size(string&,bool&)
 * Function: Makes sure the input into the string is greater than 4 and theres no random characters. Updates width_valid to true when it is.
 * *****************/
void validate_size(string& width_string, bool& width_valid){
	do{
		for(int i = 0; i < width_string.length(); i++){
			if(width_string[i] >= '0' && width_string[i] <= '9' && stoi(width_string) >= 4){
				width_valid = true;
			}else{
				width_valid = false;
				break;
			}	
		}
		if(!width_valid){
			cout<<"Invalid input for maze size. Please enter a number greater than 4:";
			getline(cin,width_string);
		}
	}while(!width_valid);


}
/********************
 * Program:validate_debug(string&,bool&)
 * Function: Makes sure the input into the string debug_string is either "true" or "false".
 * *****************/
void validate_debug(string& debug_string, bool& debug_valid){
	do{
		if(debug_string == "true" || debug_string == "false"){
			debug_valid = true;
		}else{
			debug_valid = false;
			cout<<"Invalid input for debug mode. Please enter either true or false:";
			getline(cin,debug_string);
		}
	}while(!debug_valid);

}
/********************
 * Program:play_again()
 * Function: Asks if the user wants to play again, returns true if they do, false otherwise.
 * *****************/
bool play_again(){
	bool valid = true;
	string input;
	cout<<"Do you want to play again?(0-no, 1-yes):";
	do{
		getline(cin,input);
		if(input != "0" && input != "1"){
			cout<<"Invalid input, please enter either 0 or 1:";
			valid = false;
		}else{
			valid = true;
		}
	}while(!valid);
	return stoi(input);
}
