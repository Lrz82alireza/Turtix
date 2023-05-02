#pragma once

#include "Person.hpp"
#include "Map.hpp"

class Enemy : public Person
{    
protected:
    Vector2f cur_dir; // some random dir OR a const
public:
    void default_movement(MAP &game_map);

    Enemy(string file_name, float enemy_speed_, float gravity);
    ~Enemy();
};


