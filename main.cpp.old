#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <curses.h>

bool running = false;
int w, h;
int size_y, size_x;
int mines;
int cursor_y = 0, cursor_x = 0;
bool cursor = true;
int ch;
int ctemp;
int frames = 0;

void init();
void gameloop();
void cursorp();
void render();
void update();
int checkMines(int y_pos, int x_pos);
void destroy();

int **grid;

using namespace std;

int main(int argc, char *argv[])
{

  init();

  gameloop();

  destroy();
  
  return 0;
}

void init() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  cbreak();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);

  running = true;

  srand(time(NULL));

  getmaxyx(stdscr, h, w);

  // 1 - 25A1 -  - white space
  // 2 - 25A6 -  - covered space
  // 3 - 25A3 -  - marked place
  // 4 - 2D5C -  - mine
  // 5 - 25A6 -   - covered mine
  // 6 - cursor

  size_y = 5;
  size_x = 5;
  mines = 5;

  grid = new int*[size_y];
  for(int i = 0; i < size_y; ++i) {
    grid[i] = new int[size_x];
  }

  for(int i = 0; i < size_y; ++i) {
    for(int j = 0; j < size_x; ++j) {
      grid[i][j] = 2;
    }
  }

  for(int i = 0; i < mines; i++) {
    grid[rand() % size_y][rand() % size_x] = 5;
  }
  
}

void gameloop() {

  while(running) {
    move(0, 0);
    update();
    cursorp();
    render();
    refresh();
    //sleep(1);
    frames++;
  }
  
}

void cursorp() {

  if(cursor == true) {
    ctemp = grid[cursor_y][cursor_x];
    grid[cursor_y][cursor_x] = 6;
    cursor = false;
  } else {
    grid[cursor_y][cursor_x] = ctemp;
    cursor= true;
  }
  
}

void render() {

  for(int i = 0; i < size_y; i++) {
    for(int j = 0; j < size_x; j++) {

      // 1 - white space
      // 2 - covered space
      // 3 - marked place
      // 4 - mine
      // 5 - covered mine
      // 6 - cursor
      // 7 - marked mine

      //after 11 - 19 number tiles
      
      switch(grid[i][j]) {
      case 1:
	addstr("\u25A2");
 	break;
      case 2:
        addstr("\u25A6");
	break;
      case 3:
	addstr("\u256C");
	break;
      case 4:
	addstr("+");
	break;
      case 5:
	addstr("\u25A6");
	break;
      case 6:
	addstr("\u00D7");
	break;
      case 7:
	addstr("\u256C");
	break;
      case 11:
	addstr("1");
	break;
      case 12:
	addstr("2");
	break;
      case 13:
	addstr("3");
	break;
      case 14:
	addstr("4");
	break;
      case 15:
	addstr("5");
	break;
      case 16:
	addstr("6");
	break;
      }
    }
    printw("\n");
  }

}

void update() {

  ch = getch();
  if(ch != ERR || ch != 0) {
    switch(ch) {
    case 'c':
      if(grid[cursor_y][cursor_x] == 2)	grid[cursor_y][cursor_x] = 1;
      if(grid[cursor_y][cursor_x] == 5) {
	grid[cursor_y][cursor_x] = 4;
	//TODO: Game Over
      }
      break;
    case 'v':
      if(grid[cursor_y][cursor_x] == 2) grid[cursor_y][cursor_x] = 3;
      if(grid[cursor_y][cursor_x] == 5) grid[cursor_y][cursor_x] = 7;
      break;
    case 'b':
      if(grid[cursor_y][cursor_x] == 3) grid[cursor_y][cursor_x] = 2;
      if(grid[cursor_y][cursor_x] == 7) grid[cursor_y][cursor_x] = 5;
      break;
    case KEY_UP:
      cursor = true;
      if(cursor) grid[cursor_y][cursor_x] = ctemp;
      if(cursor_y != 0){
	cursor_y--;
      }
      break;
    case KEY_DOWN:
      cursor = true;
      if(cursor) grid[cursor_y][cursor_x] = ctemp;
      if(cursor_y != size_y - 1) {
	cursor_y++;
      }
      break;
    case KEY_RIGHT:
      cursor = true;
      if(cursor) grid[cursor_y][cursor_x] = ctemp;
      if (cursor_x != size_x - 1) {
	cursor_x++;
      }
      break;
    case KEY_LEFT:
      cursor = true;
      if(cursor) grid[cursor_y][cursor_x] = ctemp;
      if (cursor_x != 0) {
     	cursor_x--;
      }
      break;

    }    
  }

  for(int i = 0; i < size_y; i++) {
    for(int j = 0; j < size_x; j++) {

      if(grid[i][j] == 1) grid[i][j] = 10 + checkMines(i, j);
      
    }
  }

}

int checkMines(int x, int y) {
  int counter = 0;
  
  if(grid[--y][--x] == 5) {
    if(y != 0 || x != 0) counter++;
  }

  if(grid[++y][--x] == 5) {
    if(x != 0 || y != size_y - 1) counter++;
  }

  if(grid[++y][++x] == 5) {
    if(y != size_y - 1 || x != size_x - 1) counter++;
  }

  if(grid[--y][++x] == 5) {
    if(y != 0 || x == size_x - 1) counter++;
  }

  if(grid[y][--x] == 5) {
    if(x != 0) counter++;
  }

  if(grid[y][++x] == 5) {
    if(x != size_x - 1) counter++;
  }

  if(grid[++y][x] == 5) {
    if(y != size_y - 1) counter++;
  }

  if(grid[--y][x] == 5) {
    if(y != 0) counter++;
  }

  return counter;
}

void destroy() {
  endwin();
}
