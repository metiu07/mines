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
    //Enable of movement keys
    keypad(stdscr, TRUE);
    //Dont show cursor
    curs_set(0);

    cur_y = 0;
    cur_x = 0;

    grid = new int*[size_x];
    for(int y = 0; y < size_x; ++y) {
        grid[y] = new int[size_y];
    }

    for(int y = 0; y < size_y; ++y) {
        for(int x = 0; x < size_x; ++x) {
            grid[x][y] = 10;
        }
    }

    grid[1][0] = 9;
    grid[3][3] = 9;
    
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

int game::countmines(int x, int y) {
    int result = 0;

    if(x != 0) {
        if (grid[x - 1][y] == 9) ++result;
    }

    if(x != size_x - 1) {
        if (grid[x + 1][y] == 9) ++result;
    }

    if(y != 0) {
        if (grid[x][y - 1] == 9) ++result;
    }

    if(y != size_y - 1) {
        if (grid[x][y + 1] == 9) ++result;
    }

    if((x != 0) && (y != 0)) {
        if (grid[x - 1][y - 1] == 9) ++result;
    }

    if((x != size_x - 1) && (y != size_y - 1)) {
        if (grid[x + 1][y + 1] == 9) ++result;
    }

    if((x != 0) && (y != size_y - 1)) {
        if (grid[x - 1][y + 1] == 9) ++result;
    }

    if((x != size_x - 1) && (y != 0)) {
        if (grid[x + 1][y - 1] == 9) ++result;
    }

    return result;
}

//Grid Codes
//0 - 8 -> numbers of adjecement mines
//9 -> mine
//10 -> hidden place without mine

void game::show(int x, int y) {

    //To much logic O.o

    if(grid[x][y] == 10)  {
        //If its not mine or black space
        //Show adjacement places
        
        grid[x][y] = countmines(x, y);

        if(x != 0) {
            show(x - 1, y);
        }

        if(x != size_x - 1) {
            show(x + 1, y);
        }

        if(y != 0) {
            show(x, y - 1);
        }

        if(y != size_y - 1) {
            show(x, y + 1);
        }

        if((x != 0) && (y != 0)) {
            show(x - 1, y - 1);
        }

        if((x != size_x - 1) && (y != size_y - 1)) {
            show(x + 1, y + 1);
        }

        if((x != 0) && (y != size_y - 1)) {
            show(x - 1, y + 1);
        }

        if((x != size_x - 1) && (y != 0)) {
            show(x + 1, y - 1);
        }


    } else {
        if(grid[cur_x][cur_y] == 9) {
            stop();
        }
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
                    case 0:
                        addch(' ');
                        break;
                    case 1: 
                        addch('1');
                        break;
                    case 2:
                        addch('2');
                        break;
                    case 3:
                        addch('3');
                        break;
                    case 4:
                        addch('4');
                        break;
                    case 5:
                        addch('5');
                        break;
                    case 6:
                        addch('6');
                        break;
                    case 7:
                        addch('7');
                        break;
                    case 8:
                        addch('8');
                        break;
                    case 9:
                        addch('#');
                        break;
                    case 10:
                        addch('#');
                        break;
                    default:
                        addch('E');
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
                if(cur_y != size_y - 1)
                    setCursor(cur_x, ++cur_y);
                break;
            case KEY_UP :
                if(cur_y != 0)
                    setCursor(cur_x, --cur_y);
                break;
            case KEY_LEFT :
                if(cur_x != 0)
                    setCursor(--cur_x, cur_y);
                break;
            case KEY_RIGHT :
                if(cur_x != size_x - 1)
                    setCursor(++cur_x, cur_y);
                break;
            case 'c' : 
                show(cur_x, cur_y);
                break;
            case 'm' :
                grid[cur_x][cur_y] = 9;
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
