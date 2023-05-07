#include "Enemy.hpp"

const int FRAMENUM = 12;

void Enemy::default_movement(bool is_move_valid , bool is_on_edge)
{
    if (!is_move_valid || is_on_edge)
    {
        this->cur_dir = {-cur_dir.x, -cur_dir.y};
        this->move(cur_dir.x, cur_dir.y);
    }
}

Enemy::Enemy(string file_name, float enemy_speed_)
    : Person(file_name, enemy_speed_)
{
    int ran = rand() % 2;
    switch (ran)
    {
    case 0:
        this->cur_dir = {1.f, 0.f};
        break;
    
    case 1:
        this->cur_dir = {-1.f, 0.f};
        break;;
    }
}

Enemy::~Enemy()
{
}

void Enemy::update_frame(int const FRAMENUM)
{
    if (cur_frame < (FRAMENUM - 1))
    {
        cur_frame += 1;
    }
    else
    {
        cur_frame = 0;
    }
}

void Enemy::move_left_animation(int const FRAMESIZE , int const FRAMENUM)
{
    if (!shield)
    {
        sprite.setScale(FRAMESIZE, FRAMESIZE);
        if (is_on_earth_())
        {
            update_frame(FRAMENUM);
            sprite.setTexture((*frames)[cur_frame]);
            sprite.setScale(FRAMESIZE, FRAMESIZE);
        }
    }
    else
    {
        sprite.setScale(FRAMESIZE, FRAMESIZE);
        if (is_on_earth_())
        {
            update_frame(FRAMENUM);
            sprite.setTexture((*shield_frames)[cur_frame]);
            sprite.setScale(FRAMESIZE, FRAMESIZE);
        }
    }
}

void Enemy::move_right_animation(int const FRAMESIZE , int const FRAMENUM)
{
    if (!shield)
    {
        sprite.setScale(-FRAMESIZE, FRAMESIZE);
        if (is_on_earth_())
        {
            update_frame(FRAMENUM);
            sprite.setTexture((*frames)[cur_frame]);
            sprite.setScale(-FRAMESIZE, FRAMESIZE);
        }
    }
    else
    {
        sprite.setScale(-FRAMESIZE, FRAMESIZE);
        if (is_on_earth_())
        {
            update_frame(FRAMENUM);
            sprite.setTexture((*shield_frames)[cur_frame]);
            sprite.setScale(-FRAMESIZE, FRAMESIZE);
        }
    }
}
