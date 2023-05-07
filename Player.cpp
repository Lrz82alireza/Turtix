#include "Player.hpp"

const String PLAYER_TEXTURE = "Images/player/0.png";
const float PLAYER_SPEED = 1.5;
const int HEALTH = 3;

const int HEIGHT = 90;
const int WIDTH = 100;
const int FRAMENUM = 16;

// Private Functions

// Accessors

// Constructors

Player::Player()
       :Person(PLAYER_TEXTURE, PLAYER_SPEED)
{
       this->health = HEALTH;
}

void Player::init_animation_frames()
{
       for (int i = 0 ; i < FRAMENUM ; i++)
       {
              Texture tmp;
              tmp.loadFromFile("Images/player/" + to_string(i) + ".png");
              frames.push_back(tmp);
       }
}


