#include "Game_manager.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{


    Game_manager *manager = new Game_manager;
    manager->run();
    
    // cout << "s" << endl;

    return 0;
}