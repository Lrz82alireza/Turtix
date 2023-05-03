#pragma once

#include <cstdlib>
#include "Person.hpp"
#include <SFML/Graphics.hpp>


class Enemy : public Person
{

protected:
    Vector2f cur_dir; // some random dir OR a const
    //bool has_shield;
public:

    //virtual void set_enemy_shield(bool clock);
    Vector2f get_cur_dir() { return cur_dir; }
    void default_movement(bool is_move_valid , bool is_on_edge);
    //bool has_enemy_shield() {return has_shield; };
    Enemy(string file_name, float enemy_speed_);
    ~Enemy();
};


