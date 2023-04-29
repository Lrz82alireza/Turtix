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
        RenderWindow * window;
        vector <RectangleShape> grounds;
        vector<vector<char>> input;

    public:
        void read_inputs(string file_name);
        void set_window(RenderWindow * window);
        void make_ground(float cur_x , float cur_y , Texture * texture);
        void make_map();
        vector <RectangleShape> get_ground();
};

