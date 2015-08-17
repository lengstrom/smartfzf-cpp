#ifndef GUARD_renderer_h
#define GUARD_renderer_h

#include <string>
#include <vector>
#include <ncurses.h>

class Renderer {
private:
    static Renderer *instance; /* to get function pointers for 
                                  c-libraries */

    std::vector<std::string> &items;
    std::string current_prompt;
    WINDOW * win;
    int win_height;
    int win_width;
    int line_to_highlight;
    int prompt_row;

    static void resize_handler(int signo);
    void highlight_line(int num);
    void start_ncurses();
    void end_ncurses();
    void update_contents();
    void render_window();
    void rerender_window(int signo);
    void set_position(int);

public:
    void write_prompt(const std::string &, int);
    void set_items(std::vector<std::string> &);
    void highlight_item(int item);

    /* reads character from stdin */
    int get_char(void);

    /* do not use generally--overwrites all text */
    void set_text(const std::vector<std::string>&);

    /* not yet implemented */
    void add_item(const std::string &);
    std::string remove_item(int index);

    Renderer(std::vector<std::string>&);
    ~Renderer();
};

#endif
