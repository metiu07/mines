all:
	g++ -o game main.cpp game.cpp -lncurses -Wall -g
	./game
