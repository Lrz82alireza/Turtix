#pragma once

#include "Person.hpp"
#include <cstdlib>

class Baby_turtle : Person
{
private:
    Vector2f cur_dir;
    bool is_free = false;
public:
    void default_movement(bool is_move_valid);

    Vector2f get_cur_dir() { return cur_dir; }
    Baby_turtle(string file_nam);
    ~Baby_turtle();
};



Baby_turtle::~Baby_turtle()
{
}
