#ifndef SMARTFZF_INCLUDE_INPUT_H_
#define SMARTFZF_INCLUDE_INPUT_H_

#include <string>
#include <ncurses.h>

class Input {
    private:
        int start_input_position_;
    public:
        Input();
        ~Input();
        void write_prompt(const std::string &);
        int read_char();
        void write_input(const std::string &);
        void write_below_input(const std::string &);
};

#endif // SMARTFZF_INCLUDE_INPUT_H_
