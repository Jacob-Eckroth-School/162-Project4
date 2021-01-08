#ifndef GAME_H
#define GAME_H
#include <vector>
#include "./room.h"
#include "./player.h"


class Game{
	private:
		vector<vector<Room>> rooms;
		int width;
		int height;
		Player player;
		bool debug;
		bool game_playing;
		bool wumpus_dead;
		bool firing_arrow;
		int pits;
		int wumpuses;
		int bats;
	public:
		
		Game();
		Game(int,int);
		Game(int,int,bool);
		Game(int,int,bool,int);
		void play();
		void print_map();
		void place_events();
		void fill_rooms();
		void set_room(int,int,char,int&);
		void set_player();
		Player& get_player();
		void print_player();
		void percept_events();
		void remove_gold();
		vector<vector<Room>>& get_rooms();
		void set_escape_rope();
		void test_if_game_over();
		void bat_move();
		void handle_room();
		void fire_arrow();
		void fire_in_direction(char);
		void kill_wumpus(int,int);
		void wumpus_move();
		void animate_arrow(char);
		void print_map_with_arrow(int,int,char);
};



#endif
