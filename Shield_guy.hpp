#pragma once

#include "Enemy.hpp"

class Shied_guy : public Enemy
{
private:

public:
    Shied_guy(string file_name);
    void set_shield();

    // animation methods
    void init_animation_frames();
};
