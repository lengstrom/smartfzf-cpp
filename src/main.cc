#include <iostream>
#include <vector>
#include "smartfzf.h"
#include <ncurses.h>

int main(int argc, char *argv[]) {
    return 0;
}

// ncurses helper functions
// call to end ncurses
void end_ncurses() {
    if (!isendwin()) {
        endwin();
    }
}

// call to start ncurses
void start_ncurses() {
    initscr();
    cbreak();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    atexit(end_ncurses);
}
