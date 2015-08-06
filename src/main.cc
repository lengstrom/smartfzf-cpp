#include <iostream>
#include <vector>
#include <csignal>
#include "smartfzf.h"
#include "renderer.h"

using std::vector;
using std::string;

static volatile sig_atomic_t resize_caught=0;

extern "C" void handle_resize(int snum)
{
    if(snum == SIGWINCH) {
        resize_caught=1;
    }
}

int main(int argc, char *argv[]) {
    std::cout << "smartfzf works!" << std::endl;
    vector<string> lines_to_render;
    lines_to_render.push_back("Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium");
    lines_to_render.push_back("o enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut ");
    lines_to_render.push_back("dipisci velit, sed quia non numquam eius modi tempora in");
    lines_to_render.push_back("consequatur, vel illum qui dolorem eum fugiat quo volupta");
    lines_to_render.push_back("consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore");

    const vector<string> &ref = lines_to_render;

    Renderer r(ref);
    r.render_window();
    std::signal(SIGWINCH, handle_resize);
    while (true) {
        if(resize_caught) {
            r.rerender_window();
            resize_caught=0;
        }
    }
    return 0;
}
