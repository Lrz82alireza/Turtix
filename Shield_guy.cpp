#include "Shield_guy.hpp"

float const enemy_speed = 1.0;
int const DIE_HARD_HEALTH = 1;

Shied_guy::Shied_guy(string file_name)
    : Enemy(file_name, enemy_speed)
{
    health = DIE_HARD_HEALTH;
    shield = false;
}

void Shied_guy::set_shield()
{
    cout << "checked";
    if(shield)
    {
        shield = false;
        cout << "set_shield" << endl;
        sprite.setColor(Color::Green);
    }
    else
    {
        shield = true;
        cout << "not_set_shield" << endl;
        sprite.setColor(Color::Blue);
    }
}
