#include "Die_hard.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 2;

Die_hard::Die_hard(string file_name)
         :Enemy(file_name, enemy_speed)
{
    health = DIE_HARD_HEALTH;
    shield = false;
}