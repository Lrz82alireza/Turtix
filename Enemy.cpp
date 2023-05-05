#include "Enemy.hpp"


void Enemy::default_movement(bool is_move_valid , bool is_on_edge)
{
    if (!is_move_valid || is_on_edge)
    {
        this->cur_dir = {-cur_dir.x, -cur_dir.y};
        this->move(cur_dir.x, cur_dir.y);
    }
}

Enemy::Enemy(Texture * texture, float enemy_speed_)
    : Person(texture, enemy_speed_)
{
    switch (rand() % 2)
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

