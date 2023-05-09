#pragma once

#include "Game.hpp"

const int NOTHING_CLICKED = -1;
const int LIMIT_FPS = 144;

enum LOBBY_OPTIONS
{
    START, 
    EXIT_LOBBY
};

enum MAP_SELECTION
{
    MAP_1,
    MAP_2,
    RETURN_MAP_SELECTION
};

enum PAUSE
{
    RESUME,
    EXIT_GAME
};

class Game_manager
{
private:
    Vector2f mous_pos;
    Event event;
    string cur_map;
    Game *game;

    bool mous_held = false;

    bool in_program = true;

    Texture *bg_texture;
    Sprite background;
    void init_background();
    
    Texture *option_txr;
    Texture *pressed_option_txr;
    void init_option();
    void to_pressed_txr(RectangleShape &shape);
    void to_normal_txr(vector<RectangleShape> &shapes);

    RenderWindow *lobby_window;

    // lobby
    void lobby();
    bool lobby_running = true;
    vector<RectangleShape> lobby_options;
    void init_lobby();

    // map_selection
    void map_selection();
    bool map_selection_running = false;
    vector<RectangleShape> map_selection_options;
    vector<string> maps;
    void init_map_selection();


    void game_run();
    bool in_game = false;

    // pause
    void pause();
    bool is_pause = false;
    vector<RectangleShape> pause_options;
    void init_pause();


    void init_windows();
    
    int get_window_event(vector<RectangleShape> &options);
    void get_mous_pos(RenderWindow &window);
    void render_window(RenderWindow &Window, vector<RectangleShape> &options, Sprite &bg);
    void run_lobby();
    void run_map_selection();
    void poll_event();
public:
    /////////////
    Game_manager();
    void render();
    void update();

    void run();
};


