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


class MAP
{
    private:
        sf::RenderWindow * window;
        std::vector <sf::RectangleShape> grounds;
        std::vector<std::vector<char>> input;

    public:
        void read_inputs(std::string file_name);
        void set_window(sf::RenderWindow * window);
        void make_ground(float cur_x , float cur_y , sf::Texture * texture);
        void make_map();
        std::vector <sf::RectangleShape> get_ground();
};

