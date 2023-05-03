#include "Die_hard.hpp"

float const enemy_speed = 1.0;
float gravity = 4.0;

Die_hard::Die_hard(string file_name)
    : Enemy(file_name, enemy_speed, gravity)
{
    health = 2;
}
