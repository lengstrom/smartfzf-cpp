#include <string>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <csignal>
#include "renderer.h"
#include <iostream>

using std::min;
using std::vector;
using std::string;

Renderer *Renderer::instance;

int Renderer::get_char(void) {
    return wgetch(win);
}

void Renderer::initialize_window() {
    getmaxyx(stdscr, win_height, win_width);
    win = newwin(win_height, win_width, 0, 0);
    keypad(win,false);
}
                              
void Renderer::rerender_window() {
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
    int num_lines_to_render = min(static_cast<int>(rendered_lines.size()), win_height);
    // should check for whether there are more than 3 lines??
    int prompt_line = win_height - 1; // line we're going to render the prompt on
    int max_chars_per_line = min(win_width, static_cast<int>(current_prompt.size()));
    // eventually show the last part of the string that's being displayed 
    render_line(prompt_line, current_prompt, max_chars_per_line);
    
    for (int line = 1; line < num_lines_to_render; line++) { 
        string curr_line = rendered_lines[line];
        int max_chars_per_line = min(win_width - WINDOW_OFFSET_LEFT, static_cast<int>(curr_line.size()));
        int row = win_height - 1 - line;
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

    wmove(win, prompt_line, current_prompt_position + WINDOW_OFFSET_LEFT);
}

void Renderer::render_line(int row, string &line, int max_chars) {
    for (int col = WINDOW_OFFSET_LEFT; col < max_chars + WINDOW_OFFSET_LEFT; col++) {
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

Renderer::Renderer(string &initial_prompt_line, vector<string> &initial_lines) : current_prompt(initial_prompt_line) , rendered_lines(initial_lines) {
    instance = this;
    std::signal(28, Renderer::resize_handler); // SIGWINCH == 28
    start_ncurses();
    initialize_window();
    line_to_highlight = 1;
    // leave one line open for diagnostics etc...
    // ^ not for now (just compressed view for now )
}

void Renderer::set_lines(vector<string> &lines) {
    rendered_lines = lines;
}

void Renderer::resize_handler(int signo) {
    instance->rerender_window();
}

void Renderer::write_prompt(const string &prompt, int position) {
    current_prompt = prompt;
    current_prompt_position = position;
}

int Renderer::highlight_item(int item) {
    line_to_highlight = item;
    return normalize_highlight_position();
}

int Renderer::adjust_highlighted_item(int offset) {
    line_to_highlight=line_to_highlight+offset;
    return normalize_highlight_position();
}

int Renderer::normalize_highlight_position() {
    // return types
    // 0 = no error, no restrictions
    // 1 = no down arrow
    // 2 = no up arrow
    if (line_to_highlight < 1) {
        line_to_highlight = 1;
        return 1;
    }

    if (line_to_highlight >= rendered_lines.size() - 1) {
        line_to_highlight=rendered_lines.size() - 1;
        return 2;
    }

    return 0;
}

int Renderer::handle_up_arrow(int a, int b) {
    return instance->adjust_highlighted_item(+1);
}

int Renderer::handle_down_arrow(int a, int b) {
    return instance->adjust_highlighted_item(-1);
}
