#pragma once

#include "Enemy.hpp"

class Shied_guy : public Enemy 
{
private:
   
public:
    Shied_guy (string file_name );
    virtual void set_shield();
};