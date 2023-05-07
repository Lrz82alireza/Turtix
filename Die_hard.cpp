#include "Die_hard.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 2;

int const FRAMENUM = 12;
const float FRAMESIZE = 0.4;

Die_hard::Die_hard(string file_name, vector<Texture> *frames_)
         :Enemy(file_name, enemy_speed , FRAMENUM , FRAMESIZE)
{
    this->frames = frames_;

    health = DIE_HARD_HEALTH;
    shield = false;
}


