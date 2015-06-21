#include <iostream>

#include "game.h"

void mainLoop();

game g;

int main(int argc, char *argv[]) {

    std::cout << "Zadaj velkost minoveho pola" << std::endl;
    int x, y;
    std::cin >> x >> y;

    g.setSize(x, y);
    g.init();

    //Start execution of game
    mainLoop();
    
    return 0;
}

void mainLoop() {

    while(g.running()) {
        g.render();
        g.update();
        g.stop();
    }

    g.destroy();

}
