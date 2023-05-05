#include "Person.hpp"

// Private Functions
void Person::init_texture(string file_name)
{
    this->texture = new Texture;
    if (!this->texture->loadFromFile(file_name))
    {
        cout << "Didnt find Player texture" << endl;
    }
}

void Person::init_sprite()
{
    this->sprite.setTexture(*this->texture);
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
Person::Person(string file_name, float person_speed_)
{
    init_texture(file_name);
    this->init_sprite();
    this->person_speed = person_speed_;
}
