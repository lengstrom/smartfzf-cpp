#ifndef GUARD_renderer_h
#define GUARD_renderer_h

#include <string>
#include <vector>
#include <ncurses.h>

struct Renderer {
    const std::vector<std::string> &lines_to_write;
    WINDOW * win;
    int win_height;
    int win_width;

    Renderer(const std::vector<std::string> &lines);
    Renderer();
    void start_ncurses();
    void end_ncurses();
    void update_contents();
    void render_window();
    void rerender_window();

    ~Renderer();
};

#endif
