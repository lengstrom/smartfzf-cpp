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
    rl_change_environment=0;
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

//Keymap Input::original_map=rl_get_keymap();
//Keymap Input::mod_map=rl_copy_keymap(Input::original_map);
//
//int Input::return_on_change(int count, int key)
//{
//    static std::string hi;
//}
//
//int Input::insert_return(int count, int key)
//{
//    rl_insert(count,key);
//    rl_done=1;
//}

/* this function is for testing
 * purposes only */
void Input::display_associated_fns()
{
    const int KSQ_LN=('Z'-'A'+1)+('z'-'a'+1);
    char *keyseqs[KSQ_LN];
    for(int i=0; i<KSQ_LN/2; i++) {
        keyseqs[i] = new char[2];
        keyseqs[i][0] = i+'a';
        keyseqs[i][1] = '\0';

        keyseqs[i+KSQ_LN/2] = new char[2];
        keyseqs[i+KSQ_LN/2][0] = i+'A';
        keyseqs[i+KSQ_LN/2][1] = '\0';
    }

    for(int i=0; i<KSQ_LN; i++) {
        std::cout << keyseqs[i] << ": " <<
            rl_function_of_keyseq(keyseqs[i],NULL,NULL) << std::endl;
    }
    std::cout << "change";
    std::cout << *rl_insert;
    std::cout << *rl_insert_text;

    char **inv_keyseqs = rl_invoking_keyseqs(rl_insert);
    for(;inv_keyseqs;inv_keyseqs++) {
        std::cout << *inv_keyseqs << std::endl;
        delete[] *inv_keyseqs;
    }

    for(int i=0; i<KSQ_LN; i++) {
        delete[] keyseqs[i];
    }
}

//void Input::set_insert_to_insret()
//{
//    char **inv_keyseqs = rl_invoking_keyseqs(rl_insert);
//    for(;inv_keyseqs;inv_keyseqs++) {
//        rl_set_key(*inv_keyseqs,insert_return,mod_map);
//    }
//}
