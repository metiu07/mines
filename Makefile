all :
	rm -f ./game
	g++ -o game main.cpp game.cpp -lncurses -Wall -g
	./game

compile : 
	rm -f ./game
	g++ -o game main.cpp game.cpp -lncurses -Wall -g

compile32 :
	rm -f ./game
	g++ -o game main.cpp game.cpp -lncurses -m32 -Wall -g

run :
	./game
