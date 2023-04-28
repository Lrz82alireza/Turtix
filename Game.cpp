#include "Game.h"

const int WIDTH = 800;
const int HEIGHT = 600;

// Private Functions
void ::Game::init_window()
{
    this->Window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "Game 1", Style::Close | Style::Titlebar);

    this->Window->setFramerateLimit(144);
}

// Functions
void ::Game::update()
{
    this->poll_events();
}

void ::Game::render()
{


    this->Window->clear(Color::Blue);

    // draw new window

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
}

Game::~Game()
{
    delete this->Window;
}
