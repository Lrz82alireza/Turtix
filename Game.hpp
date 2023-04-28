#pragma once

#ifndef SFML / Graphics.hpp
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#endif

using namespace sf;

class Game
{
private:

    // window
    RenderWindow *Window;
    Event event;

    void init_window();     
public:

    // Constructors
    Game();
    ~Game();

    // Accessors
    
    bool running();

    // Functions

    void update();
    void render();

    void poll_events();
};

