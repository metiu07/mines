#include <iostream>
#include <ncurses.h>

#include "game.h"

void mainLoop();

game g;

int main(int argc, char *argv[]) {

    //Get size of mine field from user
    std::cout << "Zadaj velkost minoveho pola" << std::endl;
    int x, y;
    std::cout << "Sirka: ";
    std::cin >> x;
    std::cout << "Vyska: ";
    std::cin >> y;

    g.setSize(x, y);
    g.init();

    //Start execution of game
    mainLoop();
    
    return 0;
}

void mainLoop() {

    //Main loop
    while(g.running()) {
        g.update();
        g.render();
    }

    g.destroy();

}
