#ifndef GUARD_renderer_h
#define GUARD_renderer_h

#include <string>
#include <vector>
#include <ncurses.h>

struct Renderer {
    std::vector<std::string> &lines_to_write;
    WINDOW * win;
    int win_height;
    int win_width;
    int line_to_highlight;

    void write(const std::string&);
    void set_text(const std::vector<std::string>&);
    Renderer(std::vector<std::string> &lines);
    void start_ncurses();
    void end_ncurses();
    void update_contents();
    void render_window();
    void rerender_window(int signo);
    void highlight_line(int num);
    
    static void resize_handler(int signo);
    ~Renderer();
private:
    static Renderer *instance;
};

#endif
