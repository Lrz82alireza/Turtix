#include "Enemy.hpp"

#include <cstdlib>

void Enemy::default_movement(MAP &game_map)
{
    this->move(cur_dir.x, cur_dir.y);
    if (!game_map.is_move_valid(this->get_sprite(), game_map.get_ground()) || 
        game_map.is_on_edge(this->get_sprite()))
    {
        this->cur_dir = {-cur_dir.x, -cur_dir.y};
        this->move(cur_dir.x, cur_dir.y);
    }
}

Enemy::Enemy(string file_name, float enemy_speed_, float gravity)
    : Person(file_name, enemy_speed_, gravity)
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
