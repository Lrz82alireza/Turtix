#include "Baby_turtle.hpp"

float BABY_TURTLE_SPEED = 1;

const int FRAMENUM = 17;
const float FRAMESIZE = 0.3;

Baby_turtle::Baby_turtle(string file_name, vector<Texture> *frames_)
    : Person(file_name, BABY_TURTLE_SPEED)
{
    this->frames = frames_;

    int ran = rand() % 2;
    switch (ran)
    {
    case 1:
    {
        this->cur_dir = {1.f, 0.f};
        break;
    }
    case 0:
        this->cur_dir = {-1.f, 0.f};
        break;
    }
    // set the first frame
    cur_frame = 0;
    sprite.setScale(FRAMESIZE, FRAMESIZE);
}

void Baby_turtle::default_movement(bool is_move_valid, bool is_in_map)
{
    if (!is_move_valid || !is_in_map)
    {
        this->cur_dir = {-cur_dir.x, -cur_dir.y};
        this->move(cur_dir.x, cur_dir.y);
    }
}

void Baby_turtle::update_frame()
{
    if (cur_frame < (FRAMENUM - 1))
    {
        cur_frame += 1;
    }
    else
    {
        cur_frame = 1;
    }
}

void Baby_turtle::move_left_animation()
{
    sprite.setScale(FRAMESIZE, FRAMESIZE);
    if (is_on_earth_())
    {
        update_frame();
        sprite.setTexture((*frames)[cur_frame]);
        sprite.setScale(FRAMESIZE, FRAMESIZE);
    }
}

void Baby_turtle::move_right_animation()
{
    sprite.setScale(-FRAMESIZE, FRAMESIZE);
    if (is_on_earth_())
    {
        update_frame();
        sprite.setTexture((*frames)[cur_frame]);
        sprite.setScale(-FRAMESIZE, FRAMESIZE);
    }
}
