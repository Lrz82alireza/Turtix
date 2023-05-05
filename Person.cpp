#include "Person.hpp"

// Private Functions

void Person::init_sprite(Texture * texture)
{
    this->sprite.setTexture(*texture);
    this->sprite.setScale(0.2, 0.2);
    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2,
                           this->sprite.getTexture()->getSize().y / 2);
}


// Accessors
void Person::move(float dir_x, float dir_y)
{
    Vector2f dir = {this->person_speed * dir_x, this->person_speed * dir_y};
    this->sprite.move(dir);
}

void Person::to_pos(Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Person::update_jump()
{
    if (this->jump_speed > 0)
        this->jump_speed -= this->gravity_acceleration;
    else
        this->jump_speed = 0;
}

// Constructors
Person::Person(Texture * texture, float person_speed_)
{
    this->init_sprite(texture);
    this->person_speed = person_speed_;
}
