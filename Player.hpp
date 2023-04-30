#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player
{
private:
    Sprite sprite;
    Texture* texture;
    int health;
    float player_speed;

    // Private Functions
    void init_texture();
    void init_sprite();
public:

    // Accessors
    void move(float dir_x, float dir_y);
    void to_portal(Vector2f pos);
    Sprite get_sprite() { return this->sprite; };

    Player();
};

