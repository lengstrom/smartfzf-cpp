#ifndef GUARD_input_h
#define GUARD_input_h
/* input.h 
 * more comments go here! */
#include <cstdio>
#include <readline/readline.h>
#include <string>
#include "renderer.h"

class Input {
    private:
        Renderer &renderer_;
        //static int return_on_change(int,int);
        //static int insert_return(int,int);
        //static Keymap original_map;
        //static Keymap mod_map;
        void display_associated_fns(void); /* for testing */
        // void set_insert_to_insret();
        FILE *ostream;
        static int rl_getc(FILE*);
        static int current_char;

    public:
        Input(Renderer&);
        ~Input();
        std::string read_char();
};

#endif // GUARD_input_h
