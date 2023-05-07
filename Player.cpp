#include "Player.hpp"

const String PLAYER_TEXTURE = "Images/player/0.png";
const float PLAYER_SPEED = 1.5;
const int HEALTH = 3;

const int FRAMENUM = 16;
const float FRAMESIZE = 0.4;

// Private Functions

// Accessors

// Constructors

Player::Player()
    : Person(PLAYER_TEXTURE, PLAYER_SPEED)
{
       this->health = HEALTH;
       init_animation_frames();
       cur_frame = 0;
       sprite.setTexture(frames[cur_frame]);
       sprite.setScale(FRAMESIZE, FRAMESIZE);
}

void Player::init_animation_frames()
{
       for (int i = 0; i < FRAMENUM; i++)
       {
              Texture tmp;
              tmp.loadFromFile("Images/player/" + to_string(i) + ".png");
              frames.push_back(tmp);
       }
}

void Player::update_frame()
{
       if (cur_frame < (FRAMENUM - 1))
       {
              cur_frame += 1;
       }
       else
       {
              cur_frame = 0;
       }
}

void Player::move_left_animation()
{
       sprite.setScale(FRAMESIZE, FRAMESIZE);
       if (is_on_earth_())
       {
              update_frame();
              sprite.setTexture(frames[cur_frame]);
              sprite.setScale(FRAMESIZE, FRAMESIZE);
       }
}

void Player::move_right_animation()
{
       sprite.setScale(-FRAMESIZE, FRAMESIZE);
       if (is_on_earth_())
       {
              update_frame();
              sprite.setTexture(frames[cur_frame]);
              sprite.setScale(-FRAMESIZE, FRAMESIZE);
       }
}


