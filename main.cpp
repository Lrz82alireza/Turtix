#include "Game.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    Game game;

    // game loop
    while (game.running())
    {
        // update
        game.update();

        // render
        game.render();
    }
    // cout << "s" << endl;

    return 0;
}