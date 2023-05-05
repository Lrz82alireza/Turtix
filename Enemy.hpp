#pragma once

#include <cstdlib>
#include "Person.hpp"
#include <SFML/Graphics.hpp>


class Enemy : public Person
{
protected:
    Vector2f cur_dir; // some random dir OR a const
    bool shield;
public:

    Vector2f get_cur_dir() { return cur_dir; }
    void default_movement(bool is_move_valid , bool is_on_edge);
    int virtual g() {return 1;};
    
    Enemy(Texture * texture , float enemy_speed_);
    ~Enemy();
};


