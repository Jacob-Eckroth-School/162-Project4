#ifndef PLAYER_H
#define PLAYER_H
class Player{
	private:
		int arrows;
		bool has_gold;
		int x;
		int y;
	public:
		Player();
		Player(int,int);
		int get_arrows();
		void set_arrows(int);
		bool get_has_gold();
		void set_has_gold(bool);
		int get_x();
		void set_x(int);
		int get_y();
		void set_y(int);
		void move(int,int,bool&,bool&);
		void deal_with_move(char,int,int,bool&,bool&);
		void cant_move(int,int,bool&,int,bool&);
		void fire_arrow(bool&);
};




#endif
