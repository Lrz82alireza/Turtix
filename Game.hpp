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

    // somthing

    bool key_held;
    double passed_time = 0.0;
    Clock cooldownClock;
    bool isCooldown = false;
    const int cooldownDuration = 300; // milliseconds

    // Resources
    Texture *bg_texture;
    Sprite background;
    Font font;
    MAP game_map;
    Player player;
    vector<Text> texts;

    // Window
    RenderWindow *map_window;
    View view;
    Event event;
    void resize_view();

    // Initialise Functions
    void init_map_window();
    void init_map(string map_name);
    void init_player();
    void init_view();
    void init_texts();
    void init_font();
    void init_background();

    void move_person(Person &person, float dir_x, float dir_y);
    void gravity_action();
    void gravity_move(Person &person);
    void babys_gravity_move();
    void delay_check();
    void default_events();
    void default_baby_turtles_movement();
    void default_enemys_movement();
    void enemys_gravity_move();
    void player_hit_event();
    void player_collect_diamond();
    void player_collect_star();
    void player_hit_baby();
    void player_hit_enemy();

    void set_enemys_shield();

    void update_texts();
public:
    // Constructors

    Game(string map_name);
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
