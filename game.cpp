#include "game.h"

#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

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

    srand(time(NULL));

    grid = new int*[size_x];
    for(int y = 0; y < size_x; ++y) {
        grid[y] = new int[size_y];
    }

    for(int y = 0; y < size_y; ++y) {
        for(int x = 0; x < size_x; ++x) {
            grid[x][y] = 10;
        }
    }

    int cur_mines = 0;
    mines = 5;

    
    while(cur_mines <= mines) {
        grid[rand() % (size_x - 1)][rand() % (size_y - 1)] = 9;
        cur_mines++;
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

int game::countmines(int x, int y) {
    int result = 0;

    if(x != 0) {
        if ((grid[x - 1][y] == 9) || (grid[x - 1][y] == 12)) ++result;
    }

    if(x != size_x - 1) {
        if ((grid[x + 1][y] == 9) || (grid[x + 1][y] == 12)) ++result;
    }

    if(y != 0) {
        if ((grid[x][y - 1] == 9) || (grid[x][y - 1] == 12)) ++result;
    }

    if(y != size_y - 1) {
        if ((grid[x][y + 1] == 9) || (grid[x][y + 1] == 12)) ++result;
    }

    if((x != 0) && (y != 0)) {
        if ((grid[x - 1][y - 1] == 9) || (grid[x - 1][y - 1] == 12)) ++result;
    }

    if((x != size_x - 1) && (y != size_y - 1)) {
        if ((grid[x + 1][y + 1] == 9) || (grid[x + 1][y + 1] == 12)) ++result;
    }

    if((x != 0) && (y != size_y - 1)) {
        if ((grid[x - 1][y + 1] == 9) || (grid[x - 1][y + 1] == 12)) ++result;
    }

    if((x != size_x - 1) && (y != 0)) {
        if ((grid[x + 1][y - 1] == 9) || (grid[x + 1][y - 1] == 12)) ++result;
    }

    return result;
}

void game::checkforwin() {
    
    for(int y = 0; y < size_y; ++y) {
        for(int x = 0; x < size_x; ++x) {
            if((grid[x][y] == 9) || (grid[x][y] == 10)) return;
        }
    }

    stop();
    return;

}

//Grid Codes
//0 - 8 -> numbers of adjecement mines
//9 -> mine
//10 -> hidden place without mine
//11 -> flag

void game::show(int x, int y) {

    //To much logic O.o

    if((grid[x][y] == 10) || (grid[x][y] == 11))  {
        //If its not mine or black space
        //Show adjacement places
        
        grid[x][y] = countmines(x, y);

        if(countmines(x, y) != 0) return;

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
        if(grid[cur_x][cur_y] == 9) stop();
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
                    case 11:
                        addch('F');
                        break;
                    case 12:
                        addch('F');
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
            case 'k' :
                if(cur_y != 0)
                    setCursor(cur_x, --cur_y);
                break;
            case 'j' :
                if(cur_y != size_y - 1)
                    setCursor(cur_x, ++cur_y);
                break;
            case 'h' :
                if(cur_x != 0)
                    setCursor(--cur_x, cur_y);
                break;
            case 'l' :
                if(cur_x != size_x - 1)
                    setCursor(++cur_x, cur_y);
                break;
            case 'c' : 
                show(cur_x, cur_y);
                break;
            case 'm' :
                //TODO: only for debuging purposes
                grid[cur_x][cur_y] = 9;
                break;
            case 'x' :
                //Set flag at cursor position
                if (grid[cur_x][cur_y] == 10) {
                    grid[cur_x][cur_y] = 11;
                } else if (grid[cur_x][cur_y] == 9) {
                    grid[cur_x][cur_y] = 12;
                } else if (grid[cur_x][cur_y] == 12) {
                    grid[cur_x][cur_y] = 9;
                } else if (grid[cur_x][cur_y] == 11) {
                    grid[cur_x][cur_y] = 10;
                }
                
                break;
            case 'q' :
                stop();
                break;
        }
    }

    checkforwin();

}

void game::destroy() {
   endwin(); 
}
