#Makefile for Wumpus
CC = g++ -std=c++11 -g
exe_file = wumpus 
$(exe_file): game.o prog.o room.o event.o empty.o wumpus.o pit.o bats.o gold.o rope.o player.o
	$(CC) game.o prog.o room.o event.o empty.o wumpus.o pit.o bats.o gold.o rope.o player.o -o $(exe_file)

%.o: %.cpp
	$(CC) -c $<
clean:
	rm -f *.out *.o $(exe_file)
