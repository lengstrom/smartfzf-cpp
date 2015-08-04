#include <iostream>
#include <vector>
#include "smartfzf.h"
#include <ncurses.h>

struct Renderer {
    vector<string> &_lines_to_write;
    WINDOW * win_;

    void render_window() {
        int win_height, win_width;
        getmaxyx(stdscr, win_height, win_width);
        win_height = win_height - 2;

        delete win_;

        WINDOW * win = newwin(win_height, win_width, 0, 0);
        win_ = win;
        
        update_contents();
        wrefresh(win);
    }

    void update_contents(){
        // do some sort of updating
        win_ 
    }

    Renderer(vector<string> & lines_to_write) {
        _lines_to_write = lines_to_write;
    }
};

int main(int argc, char *argv[]) {
    std::cout << "smartfzf works!" << std::endl;
    Renderer r = Renderer::
    // Get window dimensions
    // Initialize window
    signal(SIGWINCH, render_window);
    return 0;
}

void render_window() {

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
