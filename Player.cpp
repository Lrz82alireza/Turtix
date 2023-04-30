#include "Player.hpp"

const String PLAYER_TEXTURE = "Images/Dirt.png";
const float PLAYER_SPEED = 5;

// Private Functions
void Player::init_texture()
{
    this->texture = new Texture;
    if (!this->texture->loadFromFile(PLAYER_TEXTURE))
    {
        cout << "Didnt find Player texture" << endl;
    }
}

void Player::init_sprite()
{
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(0.5, 0.5);
    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2,
                           this->sprite.getTexture()->getSize().y / 2);
}

// Accessors
void Player::move(float dir_x, float dir_y)
{
    Vector2f dir = {this->player_speed * dir_x, this->player_speed * dir_y};
    this->sprite.move(dir);
}

void Player::to_portal(Vector2f pos)
{
    this->sprite.setPosition(pos);
}

// Constructors
Player::Player()
{
    this->init_texture();
    this->init_sprite();
    this->player_speed = PLAYER_SPEED;
}

