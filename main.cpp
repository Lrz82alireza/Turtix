#include "Game_manager.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{


    Game_manager manager;
    manager.run();

    // manager.lobby_running = true;
    // while (manager.lobby_running)
    // {
    //     manager.lobby();
    //     manager.render_window(*manager.lobby_window, manager.lobby_options, manager.background);
    //     while (manager.map_selection_running)
    //     {

    //         manager.map_selection();
    //         manager.render_window(*manager.lobby_window, manager.map_selection_options, manager.background);
    //         // while (this->in_game)
    //         // {
    //         //         // game loop
    //         //         while (game.running())
    //         //         {
    //         //             // update
    //         //             game.update();

    //         //             // render
    //         //             game.render();
    //         //         }

    //         //         while (this->is_pause)
    //         //         {
    //         //             pause();
    //         //             this->render_window(pause_window, pause_options, background);
    //         //         }
    //         //     }
    //     }
    // }


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