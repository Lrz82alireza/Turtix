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
Person::Person(string file_name, float person_speed_, float gravity_acceleration_)
{
    init_texture(file_name);
    this->init_sprite();
    this->person_speed = person_speed_;
    this->gravity_acceleration = gravity_acceleration_;
}

int Person::intersect_direct(FloatRect object1 , FloatRect object2)
{
    if (object1.intersects(object2))
    {
        if (object1.top < (object2.top + object2.height))
            {
                return 1;
            }

        if ((object1.top + object1.height) > object2.top)
            {
                return 0;
            }

        if (object1.left < (object2.left + object2.width))
            {
                return 1;
            }

        if ((object1.left + object1.width) > object2.left)
            {
                return 2;
            }
    }
    return -1;
}