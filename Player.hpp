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

    // Private Functions
    void init_texture();
    void init_sprite(Vector2f start_point);
public:
    Player(Vector2f start_point);
    ~Player();
};

