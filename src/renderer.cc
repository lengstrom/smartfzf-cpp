#include <string>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include "renderer.h"

void Renderer::render_window() {
    getmaxyx(stdscr, win_height, win_width);
    win_height = win_height - 2;
    win = newwin(win_height, win_width, 0, 0);

    update_contents();
    wrefresh(win);
}

void Renderer::rerender_window() {
    delete win;
    render_window();
}

void Renderer::~Renderer() {
    end_ncurses();
}

void Renderer::update_contents() {
    // do some sort of updating
    int num_lines_to_write = std::min(lines_to_write.size(), win_height);

    for (int line = 0; line < num_lines_to_write; line++) { // For every line in the window
        std::string curr_line = lines_to_write[line];
        int num_chars_to_write = std::min(win_width, curr_line.size())

        for (int col = 0; col < num_chars_to_write; col++){
            mvwaddch(win, win_height - line, col, curr_line[col]);
        }
    }
}

void Renderer::end_ncurses() {
    if (!isendwin()) {
        endwin();
    }
}

void Renderer::start_ncurses() {
    initscr();
    cbreak();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    atexit(end_ncurses);
}

Renderer::Renderer(const std::vector<std::string> &lines) {
    lines_to_write = lines;
    signal(SIGWINCH, render_window);
    start_ncurses();
}
