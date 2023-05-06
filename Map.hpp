#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "Die_hard.hpp"
#include "Enemy.hpp"
#include "Baby_turtle.hpp"
#include "Shield_guy.hpp"

using namespace sf;
using namespace std;

class MAP
{
private:
    vector<RectangleShape> grounds;
    vector<vector<char>> input;
    Texture *ground_texture;
    Texture *dirt_texture;
    Texture *portal_texture;
    VideoMode screen;
    RectangleShape portal;
    vector<Enemy> enemys;
    vector<Baby_turtle> baby_turtles;
    vector<Shied_guy> shildGuys;

    // Private Functions
    void init_texture();
    float calculate_width();
    float calculate_height();
    bool is_top(float x, float y);

public:
    MAP();
    void read_inputs(string file_name);
    void make_ground(float cur_x, float cur_y, Texture *texture);
    void make_portal(float cur_x, float cur_y, Texture *texture);
    void make_baby_turtle(float cur_x, float cur_y);
    void make_texture(char c, float &cur_x, float &cur_y);
    void make_map();
    void make_die_hard(float cur_x, float cur_y);
    void make_shield_guy(float cur_x, float cur_y);

    void close();
    vector<RectangleShape> *get_ground();
    RectangleShape get_portal();
    Vector2f get_screen();
    vector<Baby_turtle> &get_Babys() { return this->baby_turtles; }
    vector<Enemy> &get_enemys();
    vector<Shied_guy> &get_shield_guys();

    bool is_in_map(Sprite sprite);
    bool is_intersected(Sprite thing, RectangleShape shapes);
    bool did_it_hit(Sprite sprite, Person enemy);
    bool is_move_valid(Sprite sprite, vector<RectangleShape> *shapes); /////////////////////////
    bool is_on_edge(Sprite sprite);
};
