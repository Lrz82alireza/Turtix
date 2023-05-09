#include "Player.hpp"

const String PLAYER_TEXTURE = "Images/player/0.png";
const float PLAYER_SPEED = 1.8;
const int HEALTH = 3;

const int FRAMENUM = 16;
const float FRAMESIZE = 0.4;

const float PLAYER_TIME_ANIMATION = 1.0;
const float PLAYER_DELAY_ANIMATION = 2.0;

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
       if (is_on_earth_() && delay())
       {
              update_frame();
              sprite.setTexture(frames[cur_frame]);
              sprite.setScale(FRAMESIZE, FRAMESIZE);
       }
}

void Player::move_right_animation()
{
       sprite.setScale(-FRAMESIZE, FRAMESIZE);
       if (is_on_earth_() && delay())
       {
              update_frame();
              sprite.setTexture(frames[cur_frame]);
              sprite.setScale(-FRAMESIZE, FRAMESIZE);
       }
}

bool Player::delay()
{
       DELAY_TIME += PLAYER_TIME_ANIMATION;
       if (DELAY_TIME - PLAYER_DELAY_ANIMATION >= 0.0)
       {
              DELAY_TIME = 0.0;
              return true;
       }
       return false;
}
