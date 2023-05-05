#pragma once

#include "Enemy.hpp"

class Die_hard : public Enemy 
{
private:
   
public:
    Die_hard (string file_name );
    virtual void set_shield() {shield=false;};
};

