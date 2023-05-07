#include "Game_manager.hpp"

void Game_manager::run()
{
    while (this->lobby_running)
    {
        this->lobby();
        while (this->map_selection_running)
        {
            this->map_selection();
            while (this->in_game)
            {
                // game loop
                while (game.running())
                {
                    // update
                    game.update();

                    // render
                    game.render();
                }

                while (this->is_pause)
                {
                    pause();
                    this->render_window(pause_window, pause_options, pause_image);
                }
            }

            this->render_window(map_selection_window, map_selection_options, map_selection_image);
        }

        this->render_window(lobby_window, lobby_options, lobby_image);
    }
}

void Game_manager::get_mous_pos(RenderWindow &window)
{
    Vector2i mous_pos_i = Mouse::getPosition(window);
    mous_pos = window.mapPixelToCoords(mous_pos_i);
}

void Game_manager::render_window(RenderWindow &Window, vector<RectangleShape> &options, Image &image)
{
    Window.clear();

    Window.draw(image);

    for (auto i : options)
        Window.draw(i);

    Window.display();
}

int Game_manager::get_window_event(vector<RectangleShape> &options)
{
    for (int i = 0; i < options.size(); i++)
    {
        if (options[i].getGlobalBounds().contains(mous_pos.x, mous_pos.y))
        {
            return i;
        }
    }
    return NOTHING_CLICKED;
}

// lobby
void Game_manager::lobby()
{
    this->get_mous_pos(this->lobby_window);
    int result = this->get_window_event(this->lobby_options);

    switch (result)
    {
    case START:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->map_selection_running = true;
        }
        break;

    case EXIT_LOBBY:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->lobby_running = false;
            this->lobby_window->close();
        }
        break;
    }
}

// map_selecition
void Game_manager::map_selection()
{
    this->get_mous_pos(this->map_selection_window);
    int result = this->get_window_event(this->map_selection_options);

    switch (result)
    {
    case MAP_1:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->cur_map = this->maps[result];
            this->in_game = true;
            game = new Game(cur_map);
        }
        // go to game
        break;

    case MAP_2:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->cur_map = this->maps[result];
            this->in_game = true;
            game = new Game(cur_map);
        }
        // go to game
        break;

    case RETURN_MAP_SELECTION:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            delete (game);
            map_selection_running = false;
        }
        break;
    }
}

// pause
void Game_manager::pause()
{
    this->get_mous_pos(this->pause_window);
    int result = this->get_window_event(this->pause_options);

    switch (result)
    {
    case RESUME:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->is_pause = false;
        }
        break;

    case EXIT_GAME:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->is_pause = false;
            this->in_game = false;
            delete (this->game);
        }
        break;
    }
}
