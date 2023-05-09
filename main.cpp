#include "Game_manager.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{


    Game_manager *manager = new Game_manager;
    manager->run();

    // cout << "s" << endl;

    // Game game("input.txt");

    // game loop
    // while (game.running())
    // {
    //     // update
    //     game.update();

    //     // render
    //     game.render();
    // }

    return 0;
}