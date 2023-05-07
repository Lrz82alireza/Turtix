#include "Shield_guy.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 1;

const int FRAMENUM = 12;
const float FRAMESIZE = 0.4;

Shield_guy::Shield_guy(string file_name, vector<Texture> *frames_, vector<Texture> *shield_frames_)
    : Enemy(file_name, enemy_speed , FRAMENUM , FRAMESIZE)
{
    frames = frames_;
    shield_frames = shield_frames_;

    health = DIE_HARD_HEALTH;
    shield = false;
    sprite.setScale(FRAMESIZE , FRAMESIZE);
}

void Shield_guy::set_shield()
{
    if (shield)
    {
        shield = false;
        cout << "set_shield" << endl;
    }
    else
    {
        shield = true;
        cout << "not_set_shield" << endl;
    }
    cur_frame = 0;
}




