#include "Player.hpp"

const String PLAYER_TEXTURE = "Images/Dirt.png";
const float PLAYER_SPEED = 1;


// Private Functions

// Accessors

// Constructors

Player::Player(float gravity)
       :Person(PLAYER_TEXTURE, PLAYER_SPEED, gravity)
{
}
