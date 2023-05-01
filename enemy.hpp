#pragma once

#include "Person.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;
using namespace std;


class Enemy : public Person
{
private:

    // Private Functions

public:

    // Accessors
    Enemy(float gravity);
};
