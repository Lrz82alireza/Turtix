#pragma once

#include "Person.hpp"



class Enemy : public Person
{    
public:
    void default_movement();

    Enemy(string file_name, float enemy_speed_, float gravity);
    ~Enemy();
};
