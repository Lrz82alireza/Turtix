#include "Game.hpp"

const String LOBBY_FONT = "Fonts/AmaticSC-Regular.ttf";

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int LIMIT_FPS = 144;

// Initialise Functions
void Game::init_map_window()
{
    this->map_window = new RenderWindow(this->map.get_screen(), "Game 1", Style::Close | Style::Titlebar | Style::Resize);

    this->map_window->setFramerateLimit(LIMIT_FPS);
}

void Game::init_font()
{
    this->font.loadFromFile(LOBBY_FONT);
}

void Game::init_text()
{
    this->text.setFont(this->font);
    this->text.setString("How you doin");
    this->text.setCharacterSize(30);
    this->text.setFillColor(Color::White);
    this->text.setPosition(WIDTH / 2, HEIGHT / 2);
}

void Game::init_map()
{
    this->map.read_inputs("input.txt");
    this->map.make_map();
}

void Game::init_player()
{
    Vector2f portal_pos = {10.f, 10.f}; // getting start point location from map
    this->player.to_portal(portal_pos);
}

void Game::move_player(float dir_x, float dir_y)
{
    if (this->map.is_move_valid(this->player.get_sprite(), this->map.get_ground()))
        this->player.move(dir_x, dir_y);
}

// Functions
void Game::update()
{
    this->poll_events();
}

void Game::render()
{

    this->map_window->clear();

    this->map_window->draw(this->text);

    for (auto ground : map.get_ground())
        this->map_window->draw(ground);

    this->map_window->draw(this->player.get_sprite());

    this->map_window->display();
}

void Game::poll_events()
{
    while (this->map_window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case Event::Closed:
            this->map_window->close();
            break;

        case Event::KeyPressed:
            switch (this->event.key.code)
            {
            case Keyboard::Escape:
                this->map_window->close();
                break;
            }
            break;
        }
    }

    // player movement
    if (Keyboard::isKeyPressed(Keyboard::W))
        this->move_player(0.f, -1.f);
    if (Keyboard::isKeyPressed(Keyboard::S))
        this->move_player(0.f, 1.f);
    if (Keyboard::isKeyPressed(Keyboard::A))
        this->move_player(-1.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::D))
        this->move_player(1.f, 0.f);
}

// Accessors
bool Game::running()
{
    return this->map_window->isOpen();
}

// Constructor / destructor
Game::Game()
{
    this->init_map();
    this->init_map_window();
    this->init_font();
    this->init_text();
    this->init_player();
}

Game::~Game()
{
    delete this->map_window;
}
