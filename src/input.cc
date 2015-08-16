/* input.cc: an interface to readline 
 * more comments go here! */

#include "input.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

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

    ostream = fopen("/dev/null","w");
    rl_outstream=ostream;
    rl_callback_handler_install("",dummy);
    //set_insert_to_insret();
}

Input::~Input()
{
    fclose(ostream);
}

void Input::read_char() 
{
    int a = wgetch(renderer_.win);
    /*rl_pending_input=a;*/
    //rl_stuff_char(a);
    //fwrite(&a,sizeof(int),1,rstream);
    current_char = a;
    rl_callback_read_char();
    std::string f = rl_line_buffer;
    std::vector<std::string> z;
    z.push_back(f);
    z.push_back(f);
    renderer_.set_text(z);
    renderer_.set_position(rl_point);
}
