#include "Shield_guy.hpp"

float const enemy_speed = 1.0;
int const SHIELD_GAY_HEALTH = 1;

Shield_guy::Shield_guy(string file_name)
    : Enemy(file_name, enemy_speed)
{
    health = SHIELD_GAY_HEALTH;
}

//void Shield_guy::set_enemy_shield(bool clock)
//{
//    if (clock)
//    {
//        this->has_shield = true;
//        this->sprite.setColor(Color::Red);
//    }
//    this->has_shield = false;
//    this->sprite.setColor(Color::Blue);
//}