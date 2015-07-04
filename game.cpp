#include "game.h"

#include <curses.h>
#include <unistd.h>
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

    cur_y = 0;
    cur_x = 0;

    grid = new int*[size_x];
    for(int x = 0; x < size_x; ++x) {
        grid[x] = new int[size_y];
    }

    for(int y = 0; y < size_y; y++) {
        for(int x = 0; x < size_x; x++) {
            grid[x][y] = 1;
        }
    }
    
    run = true;

}

void game::setSize(int x, int y) {
    size_x = x;
    size_y = y;
}

void game::setCursor(int x, int y) {
    cur_x = x;
    cur_y = y;
}

int game::getSizeX() {
    return size_x;
}

int game::getSizeY() {
    return size_y;
}

int game::getCurX() {
    return cur_x;
}

int game::getCurY() {
    return cur_y;
}

bool game::running() {
    return run;
}

void game::stop() {
    run = false;
}

void game::show(int x, int y) {

    if(grid[x][y] != 2) {
        grid[x][y] = 3;
    } else {
        stop();
    }
}

void game::render() {

    erase();

    for(int y = 0; y < size_y; y++) {
        for(int x = 0; x < size_x; x++) {
            if((x == cur_x) && (y == cur_y)) {
                addch('X');
            } else {
                switch(grid[x][y]) {
                    case 1: 
                        addch('#');
                        break;
                    case 2:
                        addch('#');
                        break;
                    case 3:
                        addch(' ');
                        break;
                    default:
                        addch('X');
                }
            }
        }
        addch('\n');
    }
    
}

void game::update() {

    ch = getch();
    if(ch != ERR || ch != 0) {
        switch(ch) {
            case KEY_DOWN :
                if (cur_x  = size_x) 
                setCursor(cur_x, ++cur_y);
                break;
            case KEY_UP :
                setCursor(cur_x, --cur_y);
                break;
            case KEY_LEFT :
                setCursor(--cur_x, cur_y);
                break;
            case KEY_RIGHT :
                setCursor(++cur_x, cur_y);
                break;
            case 'c' : 
                show(cur_x, cur_y);
                break;
            case 'q' :
                stop();
                break;
        }
    }

}

void game::destroy() {
   endwin(); 
}
