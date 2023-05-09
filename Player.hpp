#pragma once

#include "Person.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;
using namespace std;


class Player : public Person
{
private:
    float DELAY_TIME = 0;
    int score = 0;

    // Private Functions
    vector<Texture> frames;
    int cur_frame;

public:

    // Accessors
    Player();

    int get_score() { return this->score; }

    void increase_score(int num) { this->score += num; }
    void init_animation_frames();
    void update_frame();
    void move_left_animation();
    void move_right_animation();
    bool delay();
    //Jump animation goes here
};

