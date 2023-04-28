#pragma once

#ifndef SFML / Graphics.hpp
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#endif

#include <sstream>

using namespace sf;

class Game
{
private:

    // Resources
    Font font;
    Text text;

    // Window
    RenderWindow *Window;
    Event event;

    // Initialise Functions
    void init_window();
    void init_font();
    void init_text();     
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

