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
    vector<Texture> *frames;
    vector<Texture> *shield_frames;
<<<<<<< HEAD

=======
>>>>>>> 0705f012fdb6ee22fd0592da4cd3b00431981a25
    int cur_frame;
    int framesize;
    int framenum;

public:
    Vector2f get_cur_dir() { return cur_dir; }
    void default_movement(bool is_move_valid , bool is_on_edge);
    bool has_shield(){return shield;};

    //animation methods
    void update_frame();
    void move_left_animation();
    void move_right_animation();
    void move_update(int framesize_ , vector<Texture> *texture);


    Enemy(string file_name, float enemy_speed_ , int freamnum_ , int framesize_);
    ~Enemy();
};
