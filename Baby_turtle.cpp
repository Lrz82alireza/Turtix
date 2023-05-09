#include "Baby_turtle.hpp"

float BABY_TURTLE_SPEED = 1;

const int FRAMENUM = 16;
const float FRAMESIZE = 0.3;

const int LOCKEDFRAMENUM = 10;

const float TIME_ANIMATION = 1.0;
const float DELAY_ANIMATION = 3.0;

const float NOT_FREE_TIME_ANIMATION = 1.0;
const float NOT_FREE_DELAY_ANIMATION = 7.0;

Baby_turtle::Baby_turtle(string file_name, vector<Texture> *frames_, vector<Texture> *default_frames_)
    : Person(file_name, BABY_TURTLE_SPEED)
{
    this->frames = frames_;
    this->default_frames = default_frames_;

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
    cur_locked_frame = 0;
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
    if (is_on_earth_() && delay())
    {
        NOT_FREE_DELAY_TIME = 0.0;
        update_frame();
        sprite.setTexture((*frames)[cur_frame]);
        sprite.setScale(FRAMESIZE, FRAMESIZE);
    }
}

void Baby_turtle::move_right_animation()
{
    sprite.setScale(-FRAMESIZE, FRAMESIZE);
    if (is_on_earth_() && delay())
    {
        update_frame();
        sprite.setTexture((*frames)[cur_frame]);
        sprite.setScale(-FRAMESIZE, FRAMESIZE);
    }
}

void Baby_turtle::update_default_frame()
{
    if (cur_locked_frame < (LOCKEDFRAMENUM - 1))
    {
        cur_locked_frame += 1;
    }
    else
    {
        cur_locked_frame = 1;
    }
}

void Baby_turtle::default_animation()
{
    sprite.setScale(FRAMESIZE, FRAMESIZE);
    if (not_free_delay())
    {
        update_default_frame();
        sprite.setTexture((*default_frames)[cur_locked_frame]);
        sprite.setScale(FRAMESIZE, FRAMESIZE);
    }
}

bool Baby_turtle::delay()
{
    DELAY_TIME += TIME_ANIMATION;
    if (DELAY_TIME - DELAY_ANIMATION >= 0.0)
    {
        DELAY_TIME = 0.0;
        return true;
    }
    return false;
}

bool Baby_turtle::not_free_delay()
{
    NOT_FREE_DELAY_TIME += NOT_FREE_TIME_ANIMATION;
    if (NOT_FREE_DELAY_TIME - NOT_FREE_DELAY_ANIMATION >= 0.0)
    {
        NOT_FREE_DELAY_TIME = 0.0;
        return true;
    }
    return false;
}
