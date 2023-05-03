#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Person
{
protected:
    Sprite sprite;
    Texture *texture;
    int health;
    float person_speed;
    float gravity_acceleration;
    float gravity_speed = 0;
    float jump_speed = 0;
    bool is_on_earth = false;

    // Private Functions
    void init_texture(string file_name);
    void init_sprite();

public:
    // Accessors
    void move(float dir_x, float dir_y);
    void set_jump(float jump_speed_) { this->jump_speed = jump_speed_; }
    void set_on_earth(bool state) { this->is_on_earth = state; }
    void set_gravity_speed(float number) { this->gravity_speed = number; }

    Sprite get_sprite() { return this->sprite; };
    float get_jump_speed() { return this->jump_speed; }
    float get_gravity_speed() { return this->gravity_speed; }
    Vector2f get_position() { return this->sprite.getPosition(); }
    bool is_on_earth_() { return this->is_on_earth; }
    void to_pos(Vector2f pos);
    void update_jump();

    // Constructors
    Person(string file_name, float person_speed_, float gravity_acceleration_);
};
