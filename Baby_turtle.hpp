#pragma once

#include "Person.hpp"

#include <cstdlib>

class Baby_turtle : public Person
{
protected:

private:
    float DELAY_TIME = 0.0;
    float NOT_FREE_DELAY_TIME = 0.0;
    Vector2f cur_dir;
    bool is_free = false;
    vector<Texture> *frames;
    vector<Texture> *default_frames;
    int cur_frame;
    int cur_locked_frame;

public:

    void set_free(bool state) { this->is_free = state; }

    bool is_free_() { return is_free; }

    void default_movement(bool is_move_valid, bool is_in_map);
    Vector2f get_cur_dir() { return cur_dir; }

    Baby_turtle(string file_name, vector<Texture> *frames_, vector<Texture> *default_frames);

    // animation frames
    void update_frame();
    void update_default_frame();
    void move_left_animation();
    void move_right_animation();
    void default_animation();
    bool delay();
    bool not_free_delay();
};