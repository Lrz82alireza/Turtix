#include "Player.hpp"

const String PLAYER_TEXTURE = "Images/Ground.png";
const float PLAYER_SPEED = 1.5;


// Private Functions

// Accessors

// Constructors

Player::Player()
       :Person(PLAYER_TEXTURE, PLAYER_SPEED)
{
}
