#include "Game_manager.hpp"

const string BACKGROUND_IM = "Images/background/lobbybg.png";
const string BUTTON_IM = "Images/background/button.png";

const float OPTION_DISTANCE = 200;


Game_manager::Game_manager()
{
    this->init_background();
    this->init_windows();
    this->init_option();
    this->init_lobby();
    this->init_map_selection();
}

void Game_manager::run()
{
    // Event event;
    // this->lobby_running = true;
    //     this->render_window(*lobby_window, lobby_options, background);
    // while (this->lobby_window->pollEvent(event))
    // {
    //     this->lobby();
    //     while (this->map_selection_running)
    //     {

    //         this->map_selection();
    //         this->render_window(*lobby_window, map_selection_options, background);
    Game game("input.txt");
            // while (this->in_game)
            // {
                    // game loop
                    while (game.running())
                    {
                        // update
                        game.update();

                        // render
                        game.render();
                    }

                //     while (this->is_pause)
                //     {
                //         pause();
                //         this->render_window(pause_window, pause_options, background);
                //     }
                // }
    //     }
    // }
}

void Game_manager::get_mous_pos(RenderWindow &window)
{
    Vector2i mous_pos_i = Mouse::getPosition(window);
    mous_pos = window.mapPixelToCoords(mous_pos_i);
}

void Game_manager::render_window(RenderWindow &Window, vector<RectangleShape> &options, Sprite &bg)
{
    Window.clear();

    Window.draw(bg);

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

void Game_manager::init_windows()
{
    this->lobby_window = new RenderWindow(VideoMode(this->background.getGlobalBounds().width, this->background.getGlobalBounds().height), "lobby", Style::Close | Style::Titlebar | Style::Resize);
    this->lobby_window->setFramerateLimit(LIMIT_FPS);
}

void Game_manager::init_background()
{
    this->bg_texture = new Texture;
    if (!bg_texture->loadFromFile(BACKGROUND_IM))
        cout << "game manager init_background" << endl;

    this->background.setTexture(*bg_texture);
    this->background.setScale(1.6, 1.6);
}

void Game_manager::init_option()
{
    option_txr = new Texture;
    if (!option_txr->loadFromFile(BUTTON_IM))
        cout << "game manager init option" << endl;
}

// lobby
void Game_manager::lobby()
{
    this->get_mous_pos(*this->lobby_window);
    int result = this->get_window_event(this->lobby_options);

    if (!this->mous_held)
    {
        switch (result)
        {
        case START:
            // check click mouse
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->map_selection_running = true;
                this->mous_held = true;
                break;
            }

        case EXIT_LOBBY:
            // check click mouse
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->lobby_running = false;
                this->lobby_window->close();
                this->mous_held = true;
                break;
            }
        default:
            this->mous_held = false;
        }
    }
}

void Game_manager::init_lobby()
{
    RectangleShape option;
    option.setTexture(option_txr);
    option.setOrigin(option.getTexture()->getSize().x / 2, option.getTexture()->getSize().y / 2);
    option.setSize(Vector2f(200.f, 100.f));

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 3);
    lobby_options.push_back(option);

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2);
    lobby_options.push_back(option);
}

// map_selecition
void Game_manager::map_selection()
{

    this->get_mous_pos(*this->lobby_window);
    int result = this->get_window_event(this->map_selection_options);

    if (!this->mous_held)
    {
        switch (result)
        {
        case MAP_1:
            // check click mouse

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->cur_map = this->maps[result];
                this->in_game = true;
                game = new Game(cur_map);
                this->mous_held = true;
                break;
            }

        case MAP_2:
            // check click mouse

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->cur_map = this->maps[result];
                this->in_game = true;
                game = new Game(cur_map);
                this->mous_held = true;
                break;
            }

        case RETURN_MAP_SELECTION:
            // check click mouse
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                delete (game);
                map_selection_running = false;
                this->mous_held = true;
                break;
            }
        default:
            this->mous_held = false;
        }
    }
}

void Game_manager::init_map_selection()
{
    RectangleShape option;
    option.setTexture(option_txr);
    option.setOrigin(option.getTexture()->getSize().x / 2, option.getTexture()->getSize().y / 2);
    option.setSize(Vector2f(200.f, 100.f));

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2 - 400);
    map_selection_options.push_back(option);

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2 - 400 + OPTION_DISTANCE);
    map_selection_options.push_back(option);

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2 - 400 + 2 * OPTION_DISTANCE);
    map_selection_options.push_back(option);
}

// pause
void Game_manager::pause()
{
    this->get_mous_pos(*this->lobby_window);
    int result = this->get_window_event(this->pause_options);

    switch (result)
    {
    case RESUME:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->is_pause = false;
        }
        return;

    case EXIT_GAME:
        // check click mouse
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->is_pause = false;
            this->in_game = false;
            delete (this->game);
        }
        return;
    }
}
