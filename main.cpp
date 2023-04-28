#include "Game.h"

#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
    Game game;

    // CircleShape shape(200.f);
    // shape.setFillColor(Color::Green);

    // game loop
    while (game.running())
    {
        // update
        game.update();

        // render
        game.render();
    }

    
    return 0;
}