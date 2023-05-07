#pragma once

#include <cstdlib>
#include "Person.hpp"
#include <SFML/Graphics.hpp>


class Enemy : public Person
{
protected:
    Vector2f cur_dir; // some random dir OR a const
    bool shield;
    //animation fields
    vector<Texture> frames;
    vector<Texture> shield_frames;
    int cur_frame;

public:
    Vector2f get_cur_dir() { return cur_dir; }
    void default_movement(bool is_move_valid , bool is_on_edge);
    bool has_shield(){return shield;};

    //animation methods
    void update_frame(int const FRAMENUM);
    void move_left_animation(int const FRAMESIZE , int const FRAMENUM);
    void move_right_animation(int const FRAMESIZE , int const FRAMENUM);


    Enemy(string file_name, float enemy_speed_);
    ~Enemy();
};
