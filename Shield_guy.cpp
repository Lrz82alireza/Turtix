#include "Shield_guy.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 1;

int const FRAMENUM = 12;
const float FRAMESIZE = 0.4;

Shied_guy::Shied_guy(string file_name)
    : Enemy(file_name, enemy_speed)
{
    health = DIE_HARD_HEALTH;
    shield = false;
    init_animation_frames();
    sprite.setScale(FRAMESIZE , FRAMESIZE);
}

void Shied_guy::set_shield()
{
    if (shield)
    {
        shield = false;
        //cout << "set_shield" << endl;
        sprite.setColor(Color::Green);
    }
    else
    {
        shield = true;
        //cout << "not_set_shield" << endl;
        sprite.setColor(Color::Blue);
    }
    cur_frame = 0;
}

void Shied_guy::init_animation_frames()
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


