#include "Game.hpp"

const String LOBBY_FONT = "Fonts/AmaticSC-Regular.ttf";

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int LIMIT_FPS = 144;
const float JUMP_SPEED = 7.5;
const float GRAVITY_SPEED = 1;
const Vector2f VIEW_SIZE = {400.f, 400.f};

void Game::resize_view()
{
    float aspect_ratio = float(this->map_window->getSize().x) / float(this->map_window->getSize().y);
    view.setSize(VIEW_SIZE * aspect_ratio);
}

// Initialise Functions
void Game::init_map_window()
{
    // this->map_window = new RenderWindow(this->map.get_screen(), "Game 1", Style::Close | Style::Titlebar | Style::Resize);
    this->map_window = new RenderWindow(VideoMode(1000, 1000), "Game 1", Style::Close | Style::Titlebar | Style::Resize);

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
    Vector2f portal_pos = this->map.get_portal().getPosition(); // getting start point location from map
    this->player.to_pos(portal_pos);
}

void Game::move_person(Person &person, float dir_x, float dir_y)
{
    Vector2f dir = {dir_x, dir_y};

    person.move(dir_x, dir_y);
    if (dir_y > 0)
        person.set_on_earth(false);
    while (!this->map.is_move_valid(this->player.get_sprite(), this->map.get_ground()))
    {
        person.move(-dir_x, -dir_y);
        if (dir_y > 0)
        {
            person.set_on_earth(true);
            person.set_jump(0);
        }
        if (dir_y < 0)
        {
            person.set_jump(0);
        }
    }
}

void Game::gravity_action()
{
    this->gravity_move(this->player);
    /*enemys and other sprites*/
}

void Game::init_view()
{
    this->view.setSize(VIEW_SIZE);
    this->view.setCenter(this->player.get_position());
    // this->view.setCenter(this->map.get_portal().getPosition());
}

void Game::gravity_move(Person &person)
{
    if (person.is_on_earth_())
        person.set_gravity_speed(GRAVITY_SPEED);
    else
        person.set_gravity_speed(person.get_gravity_speed() + GRAVITY_ACCELERATION);

    this->move_person(person, 0.f, person.get_gravity_speed());
}

void Game::delay_check()
{
    Time elapsedTime = this->cooldownClock.getElapsedTime();
    if (elapsedTime.asMilliseconds() >= this->cooldownDuration)
    {
        this->isCooldown = false;
    }
    else
    {
        this->isCooldown = true;
    }
}

void Game::person_jump(Person &person)
{
    this->move_person(person, 0.f, -person.get_jump_speed());
    person.update_jump();
}

// Functions
void Game::update()
{
    this->gravity_action();
    this->poll_events();
    this->person_jump(this->player);
    this->view.setCenter(this->player.get_position());
}

void Game::render()
{

    this->map_window->clear();

    this->map_window->draw(this->text);

    for (auto ground : map.get_ground())
        this->map_window->draw(ground);

    this->map_window->draw(map.get_portal());
    this->map_window->draw(this->player.get_sprite());

    this->map_window->setView(view);

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
        case Event::Resized:
            this->resize_view();
            break;
        case Event::KeyPressed:
            switch (this->event.key.code)
            {
            case Keyboard::Escape:
                this->map_window->close();
                break;
            case Keyboard::Space:
                delay_check();
                if (this->player.is_on_earth_() && !this->isCooldown)
                {
                    this->player.set_on_earth(false);
                    this->player.set_jump(JUMP_SPEED);

                    this->cooldownClock.restart();
                }
            }
        }
    }

    // player movement
    if (Keyboard::isKeyPressed(Keyboard::W))
        this->move_person(this->player, 0.f, -1.f);
    if (Keyboard::isKeyPressed(Keyboard::S))
        this->move_person(this->player, 0.f, 1.f);
    if (Keyboard::isKeyPressed(Keyboard::A))
        this->move_person(this->player, -1.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::D))
        this->move_person(this->player, 1.f, 0.f);
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
    this->init_view();
}

Game::~Game()
{
    delete this->map_window;
}
