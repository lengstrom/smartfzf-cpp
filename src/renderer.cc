#include <string>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <csignal>
#include "renderer.h"
#include <iostream>

using std::min;

Renderer *Renderer::instance;


void Renderer::render_window() {
    getmaxyx(stdscr, win_height, win_width);
    win_height = win_height - 1;
    win = newwin(win_height, win_width, 0, 0);

    update_contents();
    redrawwin(win);
    wrefresh(win);
}

void Renderer::rerender_window(int signo) {
    endwin();
    getmaxyx(stdscr, win_height, win_width);
    win_height = win_height - 2;
    wresize(win, win_height, win_width);

    werase(win);
    update_contents();
    wrefresh(win);
    redrawwin(win);
}

Renderer::~Renderer() {
    end_ncurses();
}

void Renderer::update_contents() {
    // do some sort of updating
    int num_lines_to_write = min(static_cast<int>(lines_to_write.size()), win_height);

    for (int line = 0; line < num_lines_to_write; line++) { // For every line in the window
        std::string curr_line = lines_to_write[line];
        int num_chars_to_write = min(win_width, static_cast<int>(curr_line.size()));

        int row = win_height - line - 2; // leave one line open for diagnostics etc... 
        if (line == line_to_highlight) {
            mvwaddch(win, row, 0, '>');
            mvwaddch(win, row, 1, ' ');
            for (int col = 2; col < num_chars_to_write; col++) {
                mvwaddch(win, row, col, curr_line[col - 2]);
            }
        } else {
            mvwaddch(win, row, 0, ' ');
            mvwaddch(win, row, 1, ' ');
            for (int col = 2; col < num_chars_to_write; col++) {
                mvwaddch(win, row, col, curr_line[col - 2]);
            }
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
    //atexit(end_ncurses);
}

Renderer::Renderer(const std::vector<std::string> &lines_to_write) : lines_to_write(lines_to_write) {
    line_to_highlight = 0;
    instance = this;
    std::signal(28, Renderer::resize_handler); // SIGWINCH == 28
    start_ncurses();
}

void Renderer::resize_handler(int signo) {
    instance->rerender_window(signo);
}
