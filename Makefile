all :
	g++ -o game main.cpp game.cpp -lncurses -Wall -g
	./game

compile : 
	g++ -o game main.cpp game.cpp -lncurses -Wall -g

compile32 :
	g++ -o game main.cpp game.cpp -lncurses -m32 -Wall -g

run :
	./game
