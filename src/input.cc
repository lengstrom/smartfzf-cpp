/* input.cc: an interface to readline 
 * more comments go here! */

#include "input.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <curses.h>

extern "C" void dummy(char *a) 
{
    (void)(a);
    return;
}

/* this might be needed */
extern "C" int has_input(void)
{
    return 0;
}

int Input::rl_getc(FILE*unused)
{
    (void)(unused);
    return current_char;
}

int Input::current_char;

Input::Input(Renderer &renderer) : renderer_(renderer)
{
    rl_prep_term_function=NULL;
    rl_deprep_term_function=NULL;

    rl_getc_function=Input::rl_getc;

    rl_bind_keyseq("\\C-[OA",Renderer::handle_up_arrow);
    rl_bind_keyseq("\\C-[OB",Renderer::handle_down_arrow);

    rl_bind_keyseq("\\C-[[A",Renderer::handle_up_arrow); 
    rl_bind_keyseq("\\C-[[B",Renderer::handle_down_arrow); 

    rl_bind_keyseq("\\C-M-OA",Renderer::handle_up_arrow); 
    rl_bind_keyseq("\\C-M-OB",Renderer::handle_down_arrow); 

    rl_bind_keyseq("\\C-M-[A",Renderer::handle_up_arrow); 
    rl_bind_keyseq("\\C-M-[B",Renderer::handle_down_arrow); 

    ostream = fopen("/dev/null","w");
    rl_outstream=ostream;
    rl_callback_handler_install("",dummy);
}

Input::~Input()
{
    fclose(ostream);
}

std::string Input::read_char() 
{
    int a = renderer_.get_char();
    current_char = a;
    rl_callback_read_char();
    std::string f = rl_line_buffer;

    renderer_.write_prompt(f,rl_point);
    return f;
}
