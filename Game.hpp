#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include "Map.hpp"
#include "Player.hpp"
#include "Baby_turtle.hpp"

#include <ctime>

using namespace sf;

class Game
{
private:

    // somthing

    bool key_held;
    double passed_time = 0.0;
    Clock cooldownClock;
    bool isCooldown = false;
    const int cooldownDuration = 300; // milliseconds


    // Resources

    Font font;
    Text text;
    MAP game_map;
    Player player;

    // Window
    RenderWindow *map_window;
    View view;
    Event event;
    void resize_view();

    // Initialise Functions
    void init_map_window();
    void init_map();
    void init_player();
    void init_view(); 
    void move_person(Person &person, float dir_x, float dir_y);
    void gravity_action();
    void babys_gravity_move();
    void gravity_move(Person &person);
    void delay_check();
    void default_events();
    void default_baby_turtles_movement();
    void default_enemys_movement();
    void enemys_gravity_move();
    void player_hit_event();
    
    void set_enemy_shield(Enemy& enemy);
    void set_enemys_shield(vector<Enemy>& enemys);

    void player_hit_baby();
    void player_hit_enemy();
public:

    // Constructors

    Game();
    ~Game();

    // Accessors

    // void close();
    bool running();

    // Functions
    void person_jump(Person &person);

    void update();
    void render();
    void poll_events();
};