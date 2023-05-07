#include "Die_hard.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 2;

int const FRAMENUM = 12;
const float FRAMESIZE = 0.4;

Die_hard::Die_hard(string file_name)
         :Enemy(file_name, enemy_speed)
{
    health = DIE_HARD_HEALTH;
    shield = false;
}

void Die_hard::init_animation_frames()
{
    for (int i = 0; i < FRAMENUM; i++)
    {
        Texture tmp;
        tmp.loadFromFile("Images/shield/set" + to_string(i) + ".png");
        frames.push_back(tmp);
    }
    for (int i = 0; i < FRAMENUM; i++)
    {
        Texture tmp;
        tmp.loadFromFile("Images/shield/dont_set" + to_string(i) + ".png");
        shield_frames.push_back(tmp);
    }
}
