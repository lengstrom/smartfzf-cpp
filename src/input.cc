#include "input.h"

/* Initializes the screen
 * for ncurses mode */
Input::Input() 
{
    initscr();
    cbreak(); // Read almost all input; C-c and C-z sent elsewhere
    noecho(); // Don't immediately put chars to screen
    keypad(stdscr,true); // Get F1-F12

    start_input_position_ = 0;
}

/* ends ncurses mode */
Input::~Input()
{
    endwin();
}

/* writes to row 0, column 0 */
void Input::write_prompt(const std::string &prompt)
{
    mvprintw(0,0,prompt.c_str());
    start_input_position_ = prompt.length();
    refresh();
}

/* gets a char from stdin */
int Input::read_char()
{
    return getch();
}

void Input::write_input(const std::string &input)
{
    mvprintw(0,start_input_position_,input.c_str());
    refresh();
}

void Input::write_below_input(const std::string &str)
{
    move(3,0);
    clrtoeol();
    mvprintw(3,0,"%s",str.c_str());
    refresh();
    move(0,start_input_position_);
}
