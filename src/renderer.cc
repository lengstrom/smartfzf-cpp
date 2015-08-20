#include <string>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <csignal>
#include "renderer.h"
#include <iostream>

using std::min;
using std::string;
Renderer *Renderer::instance;

int Renderer::get_char(void) {
    return wgetch(win);
}

void Renderer::initialize_window() {
    getmaxyx(stdscr, win_height, win_width);
    win_height = win_height - 1;
    win = newwin(win_height, win_width, 0, 0);
    keypad(win,false);

    update_contents();
    wrefresh(win);
}

void Renderer::rerender_window(int signo) {
    endwin();
    getmaxyx(stdscr, win_height, win_width);
    wresize(win, win_height, win_width);

    werase(win);
    update_contents();
    wrefresh(win);
}

Renderer::~Renderer() {
    delwin(win); // frees memory
    end_ncurses();
}

void Renderer::update_contents() {
    // write current prompt statically without having to add it to an array every time
    int num_rendered_lines = min(static_cast<int>(rendered_lines.size()), win_height);
    // should check for whether there are more than 3 lines??
    int prompt_line = 0;
    
    int max_chars_per_line = min(win_width, static_cast<int>(current_prompt.size()));
    // eventually show the last part of the string that's being displayed 
    render_line(prompt_line, current_prompt, max_chars_per_line);
    
    for (int line = 1; line < num_rendered_lines; line++) { 
        string curr_line = rendered_lines[line];
        int max_chars_per_line = min(win_width, static_cast<int>(curr_line.size()));
        int row = prompt_row - (num_rendered_lines - 1) + line + 1;
        if (line == line_to_highlight) {
            mvwaddch(win, row, 0, '>');
            mvwaddch(win, row, 1, ' ');
            render_line(row, curr_line, max_chars_per_line);
        } else {
            mvwaddch(win, row, 0, ' ');
            mvwaddch(win, row, 1, ' ');
            render_line(row, curr_line, max_chars_per_line);
        }
    }
}

void Renderer::render_line(int row, string &line, int max_chars) {
    for (int col = WINDOW_OFFSET_LEFT; col < max_chars - WINDOW_OFFSET_LEFT; col++) {
        mvwaddch(win, row, col, line[col - WINDOW_OFFSET_LEFT]);
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

Renderer::Renderer(std::vector<string> &initial_lines) : rendered_lines(initial_lines) {
    line_to_highlight = 0;
    instance = this;
    std::signal(28, Renderer::resize_handler); // SIGWINCH == 28
    start_ncurses();
    initialize_window();
    // leave one line open for diagnostics etc... 
    prompt_row = win_height-2;
    rerender_window(28);
}

void Renderer::resize_handler(int signo) {
    instance->rerender_window(signo);
}

void Renderer::write_prompt(const string &prompt, int position) {
    current_prompt = prompt;
    set_position(position);
}

void Renderer::set_position(int point) {
    wmove(win,prompt_row,point+2);
}

void Renderer::highlight_item(int item) {
    line_to_highlight=item;
    rerender_window(28);
}

void Renderer::adjust_highlighted_item(int offset) {
    line_to_highlight=line_to_highlight-offset;
    if(line_to_highlight < 0)
        line_to_highlight=0;
    if(line_to_highlight >= rendered_lines.size())
        line_to_highlight=rendered_lines.size()-1;
    rerender_window(28);
}

int Renderer::handle_up_arrow(int a, int b) {
    instance->adjust_highlighted_item(+1);
    return 0;
}

int Renderer::handle_down_arrow(int a, int b) {
    instance->adjust_highlighted_item(-1);
    return 0;
}
