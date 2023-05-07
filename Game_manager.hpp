#pragma once

#include "Game.hpp"

const int NOTHING_CLICKED = -1;

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

    // lobby
    void lobby();
    bool lobby_running = true;
    RenderWindow *lobby_window;
    vector<RectangleShape> lobby_options;
    Image lobby_image;

    // map_selection
    void map_selection();
    bool map_selection_running = false;
    RenderWindow *map_selection_window;
    vector<RectangleShape> map_selection_options;
    Image map_selection_image;

    vector<string> maps;

    // pause
    void pause();
    bool in_game = false;
    bool is_pause = true;
    RenderWindow *pause_window;
    vector<RectangleShape> pause_options;
    Image pause_image;


    
    int get_window_event(vector<RectangleShape> &options);
    void init_windows();
    void get_mous_pos(RenderWindow &window);
    void render_window(RenderWindow &Window, vector<RectangleShape> &options, Image &image);
public:
    Game_manager(/* args */);
    ~Game_manager();

    void run();
};

void Game_manager::init_windows()
{
    this->lobby_window = new RenderWindow(VideoMode(1000, 1000), "lobby", Style::Close | Style::Titlebar | Style::Resize);
    this->lobby_window->setFramerateLimit(LIMIT_FPS);

    this->pause_window = new RenderWindow(VideoMode(1000, 1000), "pause", Style::Close | Style::Titlebar | Style::Resize);
    this->pause_window->setFramerateLimit(LIMIT_FPS);

    this->select_map_window = new RenderWindow(VideoMode(1000, 1000), "map selection", Style::Close | Style::Titlebar | Style::Resize);
    this->select_map_window->setFramerateLimit(LIMIT_FPS);
}

Game_manager::Game_manager(/* args */)
{
}

Game_manager::~Game_manager()
{
}