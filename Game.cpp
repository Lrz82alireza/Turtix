#include "Game.hpp"

const String LOBBY_FONT = "Fonts/AmaticSC-Regular.ttf";

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int LIMIT_FPS = 144;
const float JUMP_SPEED = 6;
const float GRAVITY_SPEED = 0.5;
const Vector2f VIEW_SIZE = {400.f, 400.f};
const float TIME = 0.01;
const float SHIELD_TIME = 5.0;

void Game::resize_view()
{
    float aspect_ratio = float(this->map_window->getSize().x) / float(this->map_window->getSize().y);
    view.setSize(VIEW_SIZE * aspect_ratio);
}

// Initialise Functions
void Game::init_map_window()
{
    // this->map_window = new RenderWindow(this->game_map.get_screen(), "Game 1", Style::Close | Style::Titlebar | Style::Resize);
    this->map_window = new RenderWindow(VideoMode(1000, 1000), "Game 1", Style::Close | Style::Titlebar | Style::Resize);

    this->map_window->setFramerateLimit(LIMIT_FPS);
}

void Game::init_map()
{
    this->game_map.read_inputs("input.txt");
    this->game_map.make_map();
}

void Game::init_player()
{
    Vector2f portal_pos = this->game_map.get_portal().getPosition(); // getting start point location from map
    this->player.to_pos(portal_pos);
}

void Game::move_person(Person &person, float dir_x, float dir_y)
{
    person.move(dir_x, dir_y);
    if (dir_y > 0)
        person.set_on_earth(false);
    while (!this->game_map.is_move_valid(person.get_sprite(), this->game_map.get_ground()))
    {
        // bazgashty mitoone beshe ba shart khateme SPEED

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
    this->enemys_gravity_move();
    this->babys_gravity_move();
}

void Game::babys_gravity_move()
{
    vector<Baby_turtle> &babys = this->game_map.get_Babys();
    for (int i = 0; i < babys.size(); i++)
    {
        this->gravity_move(babys[i]);
    }
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

void Game::default_events()
{
    // background sound
    default_enemys_movement();
    default_baby_turtles_movement();
}

void Game::default_baby_turtles_movement()
{
    for (int i = 0; i < this->game_map.get_Babys().size(); i++)
    {
        Baby_turtle *baby = &this->game_map.get_Babys()[i];

        if (baby->is_free_())
        {
            baby->move(baby->get_cur_dir().x, baby->get_cur_dir().y);
            bool is_move_valid = this->game_map.is_move_valid(baby->get_sprite(), this->game_map.get_ground());
            bool is_in_map = this->game_map.is_in_map(baby->get_sprite());
            baby->default_movement(is_move_valid, is_in_map);
        }
    }
}

void Game::default_enemys_movement()
{
    for (int i = 0; i < this->game_map.get_enemys().size(); i++)
    {
        Enemy *enemy = &this->game_map.get_enemys()[i];

        enemy->move(enemy->get_cur_dir().x, enemy->get_cur_dir().y);
        bool is_move_valid = game_map.is_move_valid(enemy->get_sprite(), game_map.get_ground());
        bool is_on_edge = game_map.is_on_edge(enemy->get_sprite());
        enemy->default_movement(is_move_valid, is_on_edge);
    }
}

void Game::enemys_gravity_move()
{
    vector<Enemy> &enemys = this->game_map.get_enemys();
    for (int i = 0; i < enemys.size(); i++)
    {
        this->gravity_move(enemys[i]);
    }
}

void Game::player_hit_event()
{
    player_hit_enemy();
    player_hit_baby();
}

void Game::player_hit_baby()
{
    vector<Baby_turtle> &babys = this->game_map.get_Babys();
    for (int i = 0; i < babys.size(); i++)
    {
        if (this->game_map.did_it_hit(this->player.get_sprite(), babys[i]))
        {
            if (!babys[i].is_free_())
                babys[i].set_free(true);
        }
    }
}

void Game::player_hit_enemy()
{
    float player_bottom = this->player.get_sprite().getGlobalBounds().top +
                          this->player.get_sprite().getGlobalBounds().height - this->player.get_gravity_speed();

    passed_time += TIME;

    vector<Enemy> &enemys = this->game_map.get_enemys();
    vector<Shied_guy> &shieldGuys = this->game_map.get_shield_guys();

    //cout << passed_time << endl;
    set_enemys_shield(shieldGuys);

    for (int i = 0; i < enemys.size(); i++)
    {
        if (this->game_map.did_it_hit(this->player.get_sprite(), enemys[i]))
        {
            if (player_bottom < enemys[i].get_sprite().getGlobalBounds().top) 
            {
                enemys[i].reduse_health(1);
                if (!enemys[i].is_alive())
                    enemys.erase(enemys.begin() + i);
                
                this->player.set_on_earth(false);
                this->player.set_jump(JUMP_SPEED);
                this->player.set_gravity_speed(GRAVITY_SPEED);
            }
            else
            {
                this->player.reduse_health(1);
                if (!this->player.is_alive())
                    cout << "player is dead" << endl;
                this->player.to_pos(this->game_map.get_portal().getPosition());
            }
        }
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
    this->player_hit_event();
    this->poll_events();
    this->person_jump(this->player);
    this->view.setCenter(this->player.get_position());
    this->default_events();
}

void Game::render()
{

    this->map_window->clear();

    // this->map_window->draw(this->text);

    for (auto ground : *(game_map.get_ground()))
        this->map_window->draw(ground);

    this->map_window->draw(game_map.get_portal());
    this->map_window->draw(this->player.get_sprite());

    for (auto enemy : game_map.get_enemys())
        this->map_window->draw(enemy.get_sprite());

    for (auto baby : game_map.get_Babys())
        this->map_window->draw(baby.get_sprite());

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
    this->init_player();
    this->init_view();
}

Game::~Game()
{
    delete this->map_window;
}

void Game::set_enemys_shield(vector<Shied_guy> & shieldGuys)
{
    if ((passed_time) - (SHIELD_TIME) >= 0.0)
    {
        for (int i = 0; i < shieldGuys.size(); i++)
        {
            shieldGuys[i].set_shield();
        }
        passed_time = 0.0;
    }
}
