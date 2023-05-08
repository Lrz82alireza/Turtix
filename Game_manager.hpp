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
    Mouse mouse;
    Vector2f mous_pos;
    Event event;
    string cur_map;
    Game *game;

    bool mous_held = false;

    RenderWindow *lobby_window;

    Texture *bg_texture;
    Sprite background;
    void init_background();
    
    Texture *option_txr;
    void init_option();

    // lobby
    void lobby();
    bool lobby_running = false;
    vector<RectangleShape> lobby_options;
    void init_lobby();

    // map_selection
    void map_selection();
    bool map_selection_running = false;
    vector<RectangleShape> map_selection_options;
    void init_map_selection();

    vector<string> maps;

    // pause
    void pause();
    bool in_game = false;
    bool is_pause = true;
    vector<RectangleShape> pause_options;
    void init_pause();


    void init_windows();
    
    int get_window_event(vector<RectangleShape> &options);
    void get_mous_pos(RenderWindow &window);
    void render_window(RenderWindow &Window, vector<RectangleShape> &options, Sprite &bg);
public:
    Game_manager();

    void run();
};


