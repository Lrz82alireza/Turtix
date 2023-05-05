#include "Die_hard.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 2;

Die_hard::Die_hard(Texture * texture)
    : Enemy(texture, enemy_speed)
{
    health = DIE_HARD_HEALTH;
}
