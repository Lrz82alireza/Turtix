#include "Game_manager.hpp"

const string BACKGROUND_IM = "Images/background/lobbybg.png";
const string BUTTON_IM = "Images/background/button.png";
const string PRESSED_BUTTON_IM = "Images/background/pressed_button.png";

const string MAP_ADDRESS = "input.txt";

const float OPTION_DISTANCE = 200;

Game_manager::Game_manager()
{
    this->init_background();
    this->init_windows();
    this->init_option();
    this->init_lobby();
    this->init_map_selection();
    this->init_pause();
}

void Game_manager::run()
{

    while (this->in_program)
    {
        this->update();
        this->render();
    }
    // this->lobby_running = true;
    // while (this->lobby_window->isOpen())
    // {
    //     this->lobby();
    //     this->render_window(*lobby_window, lobby_options, background);
    //     while (this->map_selection_running)
    //     {

    //         this->map_selection();
    //         this->render_window(*lobby_window, map_selection_options, background);
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

void Game_manager::run_lobby()
{
    while (this->lobby_running)
    {
        this->lobby();
        this->render_window(*lobby_window, lobby_options, background);
    }
}

void Game_manager::run_map_selection()
{
    while (this->map_selection_running)
    {
        this->map_selection();
        this->render_window(*lobby_window, map_selection_options, background);
    }
}

void Game_manager::poll_event()
{
    while (this->lobby_window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case Event::Closed:
            this->in_program = false;
            this->lobby_window->close();
            break;
        }
    }
}

void Game_manager::render()
{
    this->lobby_window->clear();

    if (this->lobby_running)
        this->render_window(*lobby_window, lobby_options, background);

    if (this->map_selection_running)
        this->render_window(*lobby_window, map_selection_options, background);

    if (this->is_pause)
        this->render_window(*lobby_window, pause_options, background);

    this->lobby_window->display();
}

void Game_manager::update()
{
    this->poll_event();

    if (this->lobby_running)
        this->lobby();

    if (this->map_selection_running)
        this->map_selection();

    if (this->in_game)
        this->game_run();

    if (this->is_pause)
        this->pause();
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

void Game_manager::init_pause()
{
    RectangleShape option;
    option.setTexture(option_txr);
    option.setOrigin(option.getTexture()->getSize().x / 2, option.getTexture()->getSize().y / 2);
    option.setSize(Vector2f(200.f, 100.f));

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 3);
    pause_options.push_back(option);

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2);
    pause_options.push_back(option);
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

    pressed_option_txr = new Texture;
    if (!pressed_option_txr->loadFromFile(PRESSED_BUTTON_IM))
        cout << "game manager init option" << endl;
}

void Game_manager::to_pressed_txr(RectangleShape &shape)
{
    shape.setTexture(this->pressed_option_txr);
}

void Game_manager::to_normal_txr(vector<RectangleShape> &shapes)
{
    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i].setTexture(this->option_txr);
    }
}

// lobby
void Game_manager::lobby()
{
    this->get_mous_pos(*this->lobby_window);
    int result = this->get_window_event(this->lobby_options);

    switch (result)
    {
    case START:
        // check click mouse
        to_pressed_txr(this->lobby_options[START]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->lobby_running = false;
                this->map_selection_running = true;
                this->mous_held = true;
            }
        }
        break;
    case EXIT_LOBBY:
        // check click mouse
        to_pressed_txr(this->lobby_options[EXIT_LOBBY]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->in_program = false;
                this->lobby_running = false;
                this->lobby_window->close();
                this->mous_held = true;
            }
        }
        break;
    case NOTHING_CLICKED:
        this->to_normal_txr(this->lobby_options);
        break;
    }
    if (Mouse::isButtonPressed(Mouse::Left))
        this->mous_held = true;
    else
        this->mous_held = false;
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

    switch (result)
    {
    case MAP_1:
        // check click mouse
        to_pressed_txr(this->map_selection_options[MAP_1]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->map_selection_running = false;
                this->cur_map = this->maps[result];
                this->in_game = true;

                game = new Game(cur_map);

                this->mous_held = true;
            }
        }
        break;

    case MAP_2:
        // check click mouse
        to_pressed_txr(this->map_selection_options[MAP_2]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->map_selection_running = false;
                this->cur_map = this->maps[result];
                this->in_game = true;
                game = new Game(cur_map);
                this->mous_held = true;
            }
        }
        break;

    case RETURN_MAP_SELECTION:
        // check click mouse
        to_pressed_txr(this->map_selection_options[RETURN_MAP_SELECTION]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->lobby_running = true;
                this->map_selection_running = false;
                this->mous_held = true;
            }
        }
        break;
        
    case NOTHING_CLICKED:
        this->to_normal_txr(this->map_selection_options);
        break;
    }

    if (Mouse::isButtonPressed(Mouse::Left))
        this->mous_held = true;
    else
        this->mous_held = false;
}

void Game_manager::init_map_selection()
{
    // init maps
    this->maps.push_back(MAP_ADDRESS);
    this->maps.push_back(MAP_ADDRESS);

    // options
    RectangleShape option;
    option.setTexture(option_txr);
    option.setOrigin(option.getTexture()->getSize().x / 2, option.getTexture()->getSize().y / 2);
    option.setSize(Vector2f(200.f, 100.f));

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2 - 300);
    map_selection_options.push_back(option);

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2 - 300 + OPTION_DISTANCE);
    map_selection_options.push_back(option);

    option.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2,
                       background.getGlobalBounds().top + background.getGlobalBounds().height / 2 - 300 + 2 * OPTION_DISTANCE);
    map_selection_options.push_back(option);
}

void Game_manager::game_run()
{
    this->lobby_window->close();
    game->run_game();
    while (game->running())
    {
        // update
        game->update();

        // render
        game->render();
    }
    this->init_windows();
    this->in_game = false;
    this->is_pause = true;
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
        to_pressed_txr(this->pause_options[RESUME]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->is_pause = false;
                this->in_game = true;
            }
        }
        break;

    case EXIT_GAME:
        // check click mouse
        to_pressed_txr(this->pause_options[EXIT_GAME]);
        if (!this->mous_held)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                this->map_selection_running = true;
                this->is_pause = false;
                this->in_game = false;
                delete (this->game);
            }
        }
        break;
    case NOTHING_CLICKED:
        this->to_normal_txr(this->pause_options);
        break;
    }
    if (Mouse::isButtonPressed(Mouse::Left))
        this->mous_held = true;
    else
        this->mous_held = false;
}
