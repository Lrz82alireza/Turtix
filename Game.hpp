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

const float GRAVITY_ACCELERATION = 0.2;

class Game
{
private:

    // somthing
    bool key_held;

    Clock cooldownClock;
    bool isCooldown = false;
    const int cooldownDuration = 300; // milliseconds


    // Resources
    Font font;
    Text text;
    MAP game_map;
    Player player = Player(GRAVITY_ACCELERATION);

    // Window
    RenderWindow *map_window;
    View view;
    Event event;
    void resize_view();

    // Initialise Functions
    void init_map_window();
    void init_font();
    void init_text();
    void init_map();
    void init_player();
    void init_view(); 
    void move_person(Person &person, float dir_x, float dir_y);
    void gravity_action();
    void gravity_move(Person &person);
    void delay_check();
    void default_events();
public:

    // Constructors
    Game();
    ~Game();

    // Accessors
    
    bool running();

    // Functions
    void person_jump(Person &person);

    void update();
    void render();
    void poll_events();
};

