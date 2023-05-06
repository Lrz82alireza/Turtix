#pragma once

#include "Person.hpp"

#include <cstdlib>

class Baby_turtle : public Person
{
private:
    Vector2f cur_dir;
    bool is_free = false;
public:

    void set_free(bool state) { this->is_free = state; }

    bool is_free_() { return is_free; } 

    void default_movement(bool is_move_valid, bool is_in_map);
    Vector2f get_cur_dir() { return cur_dir; }

    Baby_turtle(string file_nam);
};