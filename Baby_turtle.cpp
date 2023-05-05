#include "Baby_turtle.hpp"

float BABY_TURTLE_SPEED = 1;

Baby_turtle::Baby_turtle(string file_name)
            :Person(file_name, BABY_TURTLE_SPEED)
{
    switch (rand() % 2)
    {
    case 0:
        this->cur_dir = {1.f, 0.f};
        break;
    
    case 1:
        this->cur_dir = {-1.f, 0.f};
        break;;
    }
}

void Baby_turtle::default_movement(bool is_move_valid)
{
    if (!is_move_valid)
    {
        this->cur_dir = {-cur_dir.x, -cur_dir.y};
        this->move(cur_dir.x, cur_dir.y);
    }
}