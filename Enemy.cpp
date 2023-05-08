#include "Enemy.hpp"

const int FRAMENUM = 12;

const float TIME_ANIMATION = 0.3;
const float DELAY_ANIMATION = 5.0;
float DELAY_TIME_ANIMATION = 0.0;


void Enemy::default_movement(bool is_move_valid, bool is_on_edge)
{
    if (!is_move_valid || is_on_edge)
    {
        this->cur_dir = {-cur_dir.x, -cur_dir.y};
        this->move(cur_dir.x, cur_dir.y);
    }
}

Enemy::Enemy(string file_name, float enemy_speed_, int freamnum_, float framesize_)
    : Person(file_name, enemy_speed_)
{
    framenum = freamnum_;
    framesize = framesize_;
    cur_frame = 0;

    int ran = rand() % 2;
    switch (ran)
    {
    case 0:
        this->cur_dir = {1.f, 0.f};
        break;

    case 1:
        this->cur_dir = {-1.f, 0.f};
        break;
        ;
    }
}

Enemy::~Enemy()
{
}

void Enemy::update_frame()
{
    if (cur_frame < (framenum - 1))
    {
        cur_frame += 1;
    }
    else
    {
        cur_frame = 0;
    }
}

void Enemy::move_update(float framesize_x, float framesize_y, vector<Texture> *texture)
{
    sprite.setScale(framesize_x, framesize_y);
    if (is_on_earth_() && delay())
    {
        update_frame();
        sprite.setTexture((*texture)[cur_frame]);
        sprite.setScale(framesize_x, framesize_y);
    }
}

void Enemy::move_left_animation()
{
    if (!shield)
    {
        move_update(framesize, framesize, frames);
    }
    else
    {
        move_update(framesize, framesize, shield_frames);
    }
}

void Enemy::move_right_animation()
{
    if (!shield)
    {
        move_update(-framesize, framesize, frames);
    }
    else
    {
        move_update(-framesize, framesize, shield_frames);
    }
}

bool Enemy::delay()
{
    DELAY_TIME_ANIMATION += TIME_ANIMATION;
    if (DELAY_TIME_ANIMATION - DELAY_ANIMATION >= 0.0)
    {
        DELAY_TIME_ANIMATION = 0.0;
        return true;
    }
    return false;
}