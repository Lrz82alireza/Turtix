#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include "Map.hpp"
#include "Player.hpp"
using namespace sf;

class Game
{
private:

    // Resources
    Font font;
    Text text;
    MAP map;
    Player player;

    // Window
    RenderWindow *map_window;
    Event event;

    // Initialise Functions
    void init_map_window();
    void init_font();
    void init_text();
    void init_map();
    void init_player(); 
    void move_player(float dir_x, float dir_y);    
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

