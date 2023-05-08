#pragma once

#include "Enemy.hpp"

class Shield_guy : public Enemy
{
private:

public:
    Shield_guy(string file_name, vector<Texture> *frames_, vector<Texture> *shield_frames_);
    void set_shield();
    // animation methods
};
