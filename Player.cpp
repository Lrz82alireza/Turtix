#include "Player.hpp"

const String PLAYER_TEXTURE = "lublub";

// Private Functions
void Player::init_texture()
{
    this->texture = new Texture;
    if (!this->texture->loadFromFile(PLAYER_TEXTURE))
    {
        cout << "Didnt find Player texture" << endl;
    }
}

void Player::init_sprite(Vector2f start_point)
{
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2,
                           this->sprite.getTexture()->getSize().y / 2);
    this->sprite.setPosition(start_point);
}

// Constructors
Player::Player(Vector2f start_point)
{
    this->init_texture();
    this->init_sprite(start_point);
}