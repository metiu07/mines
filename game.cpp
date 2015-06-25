#include "game.h"

#include <curses.h>
#include <iostream>

using namespace std;

game::game() {
    cout << "[+] Debug: Game constructor..." << endl;
}

void game::init() {
    cout << "[+] Debug: Game initialization..." << endl;
    //Initializes standart ncurses screen
    initscr();
    //Dont output pressed keys
    noecho();
    //Special handlig of keys
    cbreak();
    nodelay(stdscr, TRUE);
    //Use of movement keys
    keypad(stdscr, TRUE);
    //Dont show cursor
    curs_set(0);

    grid = new int*[size_y];
    for(int x = 0; x < size_x; ++x)
        grid[x] = new int[size_x];

    for(int y = 0; y < size_y; y++) {
        for(int x = 0; x < size_x; x++) {
            grid[y][x] = 1;
        }
    }

}

void game::setSize(int x, int y) {
    size_x = x;
    size_y = y;
}

int game::getSizeX() {
    return size_x;
}

int game::getSizeY() {
    return size_y;
}

bool game::running() {
    return run;
}

void game::stop() {
    run = false;
}

void game::render() {

    for(int y = 0; y < size_y; y++) {
        for(int x = 0; x < size_x; x++) {
            switch(grid[y][x]) {
                case 0: 
                    addch('#');
                    break;
                default:
                    addch('X');
            }
        }
    }
    
}

void game::update() {

    ch = getch();
    if(ch != ERR || ch != 0) {
    }

}

void game::destroy() {
   endwin(); 
}
