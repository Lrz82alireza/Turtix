#include "Game.hpp"

const String LOBBY_FONT = "Fonts/AmaticSC-Regular.ttf";

const int WIDTH = 800;
const int HEIGHT = 600;
const int LIMIT_FPS = 144;

// Initialise Functions
void ::Game::init_window()
{
    this->Window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "Game 1", Style::Close | Style::Titlebar);

    this->Window->setFramerateLimit(LIMIT_FPS);
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
    this->map.set_window(Window);
    this->map.make_map();
}

// Functions
void ::Game::update()
{
    this->poll_events();
}

void ::Game::render()
{

    this->Window->clear();

    // draw new window
    this->Window->draw(this->text);

    for (auto ground : map.get_ground())
        this->Window->draw(ground);
    
    this->Window->display();
}

void Game::poll_events()
{
    while (this->Window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case Event::Closed:
            this->Window->close();
            break;

        case Event::KeyPressed:
            switch (this->event.key.code)
            {
            case Keyboard::Escape:
                this->Window->close();
                break;

            default:
                break;
            }
            break;
        }
    }
}

// Accessors
bool Game::running()
{
    return this->Window->isOpen();
}

// Constructor / destructor
Game::Game()
{
    this->init_window();
    this->init_font();
    this->init_text();
    this->init_map();
}

Game::~Game()
{
    delete this->Window;
}
