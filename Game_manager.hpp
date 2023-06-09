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

enum LOSE
{
    PLAY_AGAIN,
    RETURN_LOSE
};

enum WIN
{
    CONTINUE
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
    RectangleShape make_option(Texture *texture);

    RenderWindow *lobby_window;

    // lose_scene
    void lose();
    bool lose_running = false;
    vector<RectangleShape> lose_options;
    void init_lose();

    // win_scene
    void win();
    bool win_running = false;
    vector<RectangleShape> win_options;
    void init_win();

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

    // game
    void game_run();
    bool in_game = false;
    void manage_end_game();

    // pause
    void pause();
    bool is_pause = false;
    vector<RectangleShape> pause_options;
    void init_pause();

    Font menu_font;
    void init_font();
    vector<Text> win_texts;
    vector<Text> lose_texts;
    vector<Text> lobby_texts;
    vector<Text> level_texts;
    vector<Text> pause_texts;
    vector<Text> producer_texts;
    void init_texts();

    void init_producer_texts();

    void init_windows();

    int get_window_event(vector<RectangleShape> &options);
    void get_mous_pos(RenderWindow &window);
    void render_window(RenderWindow &Window, vector<RectangleShape> &options, Sprite &bg, vector<Text> &texts);
    void poll_event();

public:

    Game_manager();
    void render();
    void update();

    void run();
};
