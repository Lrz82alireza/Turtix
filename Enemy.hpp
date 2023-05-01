#pragma once

#include "Person.hpp"



class Enemy : public Person
{    
public:
    void default_movement();

    Enemy(string file_name, float enemy_speed_, float gravity);
    ~Enemy();
};

Enemy::Enemy(string file_name, float enemy_speed_, float gravity)
      :Person(file_name, enemy_speed_, gravity)
{

}

Enemy::~Enemy()
{
}
