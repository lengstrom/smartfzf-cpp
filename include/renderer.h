#ifndef GUARD_renderer_h
#define GUARD_renderer_h

#include <string>
#include <vector>
#include <ncurses.h>

class Renderer {
private:
    static Renderer *instance; /* to get function pointers for c-libraries */
    std::vector<std::string> &rendered_lines;
    WINDOW * win;
    int win_height;
    const int WINDOW_OFFSET_LEFT = 2;
    int win_width;
    int line_to_highlight;
    bool should_render = true;
    int current_prompt_position = 0; // cursor position
    std::string & current_prompt;

    static void resize_handler(int signo);
    void highlight_line(int num);
    void start_ncurses();
    void end_ncurses();
    void update_contents();
    void render_window();
    void initialize_window();
    void render_line(int, std::string &, int);

public:
    // rerender window separately with another function call - shouldn't rerender every single time that we update something
    void write_prompt(const std::string &, int);
    void highlight_item(int);
    void adjust_highlighted_item(int);
    void rerender_window();
    void set_lines(std::vector<std::string> &);
    static int handle_up_arrow(int,int);
    static int handle_down_arrow(int,int);
    
    /* reads character from stdin */
    int get_char(void);
    Renderer(std::string&, std::vector<std::string>&);
    ~Renderer();
};

#endif
