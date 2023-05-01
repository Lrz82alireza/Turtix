#include "Public_functions.hpp"

enum
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    DONT
};

int intersect_direct(FloatRect object1 , FloatRect object2)
{
    if (object1.intersects(object2))
    {
        if (object1.top < (object2.top + object2.height))
            {
                return DOWN;
            }

        if ((object1.top + object1.height) > object2.top)
            {
                return UP;
            }

        if (object1.left < (object2.left + object2.width))
            {
                return RIGHT;
            }

        if ((object1.left + object1.width) > object2.left)
            {
                return LEFT;
            }
    }
    return DONT;
}