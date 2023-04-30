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

using namespace sf;
using namespace std;


class MAP
{
    private:
        vector <RectangleShape> grounds;
        vector<vector<char>> input;
        Texture* ground_texture;
        Texture* dirt_texture;
        Texture* portal_texture;
        VideoMode screen;
        RectangleShape portal;
       
        // Private Functions
        void init_texture();
        float calculate_widht();
        float calculate_height();
        bool is_top(float x , float y);
    public:
        MAP();
        void read_inputs(string file_name);
        void make_ground(float cur_x , float cur_y , Texture * texture);
        void make_portal(float cur_x, float cur_y, Texture *texture);
        void make_map();
        void make_texture(char c , float &cur_x , float &cur_y);
        vector <RectangleShape> get_ground();
        VideoMode get_screen();
        bool is_intersected(Sprite thing , RectangleShape shapes);
        bool is_move_valid(Sprite sprite , vector<RectangleShape> shape, RectangleShape &intersected_shape);
};

