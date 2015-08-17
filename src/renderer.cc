#include <string>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <csignal>
#include "renderer.h"
#include <iostream>

using std::min;

Renderer *Renderer::instance;

int Renderer::get_char(void)
{
    return wgetch(win);
}

void Renderer::render_window() {
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
    win_height = win_height - 2;
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
    std::vector<std::string> lines_to_write = 
        std::vector<std::string>(items);

    lines_to_write.push_back(current_prompt);

    int num_lines_to_write = min(static_cast<int>(lines_to_write.size()), win_height);

    for (int line = 0;
            line!=num_lines_to_write; line++) { 
        std::string curr_line = lines_to_write[line];
        int num_chars_to_write = min(win_width, static_cast<int>(curr_line.size()));

        int row = prompt_row - (num_lines_to_write-1) + line; 
        if (line == line_to_highlight) {
            mvwaddch(win, row, 0, '>');
            mvwaddch(win, row, 1, ' ');
            for (int col = 2; col < num_chars_to_write+2; col++) {
                mvwaddch(win, row, col, curr_line[col - 2]);
            }
        } else {
            mvwaddch(win, row, 0, ' ');
            mvwaddch(win, row, 1, ' ');
            for (int col = 2; col < num_chars_to_write+2; col++) {
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

Renderer::Renderer(std::vector<std::string> &initial_text) : items(initial_text) {
    line_to_highlight = 0;

    instance = this;
    std::signal(28, Renderer::resize_handler); // SIGWINCH == 28
    start_ncurses();
    render_window();
    // leave one line open for diagnostics etc... 
    prompt_row = win_height-2;
    rerender_window(28);
}

void Renderer::resize_handler(int signo) {
    instance->rerender_window(signo);
}

void Renderer::write_prompt(const std::string &prompt, int position)
{
    current_prompt = prompt;
    rerender_window(28);
    set_position(position);
}

void Renderer::set_items(std::vector<std::string> &input)
{
    items = input;
}

void Renderer::set_position(int point)
{
    wmove(win,prompt_row,point+2);
}

void Renderer::highlight_item(int item)
{
    line_to_highlight=item;
    rerender_window(28);
}

void Renderer::adjust_highlighted_item(int offset)
{
    line_to_highlight=line_to_highlight-offset;
    if(line_to_highlight < 0)
        line_to_highlight=0;
    if(line_to_highlight >= items.size())
        line_to_highlight=items.size()-1;
    rerender_window(28);
}

int Renderer::handle_up_arrow(int a, int b)
{
    instance->adjust_highlighted_item(+1);
    return 0;
}

int Renderer::handle_down_arrow(int a, int b)
{
    instance->adjust_highlighted_item(-1);
    return 0;
}
