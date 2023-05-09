#include "Game.hpp"

const String LOBBY_FONT = "Fonts/AmaticSC-Regular.ttf";
const string BACKGROUND_IM = "Images/background/mainbg.png";

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int LIMIT_FPS = 144;
const Vector2f VIEW_SIZE = {400.f, 400.f};

const int DIAMOND_SCORE = 1;
const int STAR_SCORE = 5;

const float JUMP_SPEED = 4;
const float GRAVITY_SPEED = 0.8;
const float STANDARD_ERROR = 0.f;

const float TIME = 0.03;
const float SHIELD_TIME = 11.0;

void Game::resize_view()
{
    float aspect_ratio = float(this->map_window->getSize().x) / float(this->map_window->getSize().y);
    view.setSize(VIEW_SIZE * aspect_ratio);
}

// Initialise Functions
void Game::init_map_window()
{
    // this->map_window = new RenderWindow(VideoMode(this->game_map.get_screen().x, this->game_map.get_screen().y), "Game 1", Style::Close | Style::Titlebar | Style::Resize);
    this->map_window = new RenderWindow(VideoMode(1000, 1000), "Game 1", Style::Close | Style::Titlebar | Style::Resize);

    this->map_window->setFramerateLimit(LIMIT_FPS);
}

void Game::init_map(string map_name)
{
    this->game_map.read_inputs(map_name);
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
        if (this->game_map.is_intersected(this->game_map.get_Babys()[i].get_sprite(), this->game_map.get_portal()))
        {
            if (this->game_map.get_Babys()[i].get_sprite().getPosition().x == this->game_map.get_portal().getPosition().x +
                                                                                  this->game_map.get_portal().getGlobalBounds().width / 2)
                this->game_map.get_Babys().erase(this->game_map.get_Babys().begin() + i);
        }
        Baby_turtle *baby = &this->game_map.get_Babys()[i];

        if (baby->is_free_())
        {
            baby->move(baby->get_cur_dir().x, baby->get_cur_dir().y);
            bool is_move_valid = this->game_map.is_move_valid(baby->get_sprite(), this->game_map.get_ground());
            bool is_in_map = this->game_map.is_in_map(baby->get_sprite());
            baby->default_movement(is_move_valid, is_in_map);
            if (baby->get_cur_dir().x > 0)
            {
                baby->move_right_animation();
            }
            else
            {
                baby->move_left_animation();
            }
        }
        else
        {
            baby->default_animation();
        }
    }
}

void Game::default_enemys_movement()
{
    passed_time += TIME;
    // cout << passed_time << endl;
    set_enemys_shield();

    for (int i = 0; i < this->game_map.get_enemys().size(); i++)
    {
        Enemy *enemy = this->game_map.get_enemys()[i];

        enemy->move(enemy->get_cur_dir().x, enemy->get_cur_dir().y);
        bool is_move_valid = game_map.is_move_valid(enemy->get_sprite(), game_map.get_ground());
        bool is_on_edge = game_map.is_on_edge(enemy->get_sprite());
        enemy->default_movement(is_move_valid, is_on_edge);

        if (enemy->get_cur_dir().x > 0)
        {
            enemy->move_right_animation();
        }
        else
        {
            enemy->move_left_animation();
        }
    }
}

void Game::enemys_gravity_move()
{
    vector<Enemy *> &enemys = this->game_map.get_enemys();
    for (int i = 0; i < enemys.size(); i++)
    {
        this->gravity_move(*enemys[i]);
    }
}

void Game::player_hit_event()
{
    player_hit_enemy();
    player_hit_baby();
    player_collect_diamond();
    player_collect_star();
}

void Game::player_collect_diamond()
{
    vector<RectangleShape> &diamonds = this->game_map.get_diamonds();
    for (int i = 0; i < diamonds.size(); i++)
    {
        if (this->game_map.is_intersected(this->player.get_sprite(), diamonds[i]))
        {
            this->player.increase_score(DIAMOND_SCORE);
            diamonds.erase(diamonds.begin() + i);
        }
    }
}
void Game::player_collect_star()
{
    vector<RectangleShape> &stars = this->game_map.get_stars();
    for (int i = 0; i < stars.size(); i++)
    {
        if (this->game_map.is_intersected(this->player.get_sprite(), stars[i]))
        {
            this->player.increase_score(STAR_SCORE);
            stars.erase(stars.begin() + i);
        }
    }
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

    vector<Enemy *> &enemys = this->game_map.get_enemys();

    for (int i = 0; i < enemys.size(); i++)
    {
        if (this->game_map.did_it_hit(this->player.get_sprite(), *enemys[i]))
        {
            if (player_bottom - this->player.get_gravity_speed() <= enemys[i]->get_sprite().getGlobalBounds().top + STANDARD_ERROR && !enemys[i]->has_shield())
            {
                enemys[i]->reduse_health(1);
                if (!enemys[i]->is_alive())
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
                Vector2f loc;
                loc.x = this->game_map.get_portal().getPosition().x + this->game_map.get_portal().getGlobalBounds().width/2;
                loc.y = this->game_map.get_portal().getPosition().y + this->game_map.get_portal().getGlobalBounds().height/2;
                this->player.to_pos(loc);
            }
        }
    }
}

void Game::player_in_void()
{
    if (player.get_sprite().getGlobalBounds().top > this->game_map.get_screen().y + 200)
    {
        this->player.reduse_health(1);
        if (!this->player.is_alive())
            cout << "player is dead" << endl;
        this->player.to_pos(this->game_map.get_portal().getPosition());
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
    this->game_map.set_stars_animation();
    this->game_map.set_diamonds_animation();
    this->gravity_action();
    this->poll_events();
    this->person_jump(this->player);
    this->default_events();
    this->player_hit_event();
    this->player_in_void();
    this->view.setCenter(this->player.get_position());
    this->update_texts();
    this->game_map.set_portal_animation();
}

void Game::render()
{
    this->map_window->clear();

    this->map_window->draw(background);

    this->map_window->draw(game_map.get_portal());

    for (auto ground : *(game_map.get_ground()))
        this->map_window->draw(ground);

    this->map_window->draw(this->player.get_sprite());

    for (auto star : game_map.get_stars())
        this->map_window->draw(star);

    for (auto enemy : game_map.get_enemys())
        this->map_window->draw(enemy->get_sprite());

    for (auto baby : game_map.get_Babys())
        this->map_window->draw(baby.get_sprite());

    for (auto diamond : game_map.get_diamonds())
        this->map_window->draw(diamond);

    this->map_window->setView(view);

    for (auto i : this->texts)
        this->map_window->draw(i);

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
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        this->move_person(this->player, -1.f, 0.f);
        player.move_left_animation();
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        this->move_person(this->player, 1.f, 0.f);
        player.move_right_animation();
    }
}

void Game::run_game()
{
    if (!this->map_window->isOpen())
    {
        this->map_window->create(VideoMode(1000, 1000), "Game 1", Style::Close | Style::Titlebar | Style::Resize);
        this->map_window->setFramerateLimit(LIMIT_FPS);
    }
}

// Accessors
bool Game::running()
{
    return this->map_window->isOpen();
}

// Constructor / destructor
Game::Game(string map_name)
{
    this->init_map(map_name);
    this->init_map_window();
    this->init_player();
    this->init_view();
    this->init_font();
    this->init_texts();
    this->init_background();
}

Game::Game()
{
}

Game::~Game()
{
    delete this->map_window;
}

void Game::set_enemys_shield()
{
    if (passed_time - SHIELD_TIME >= 0.0)
    {
        for (int i = 0; i < game_map.get_shield_guys().size(); i++)
        {
            Shield_guy *shield_guy = game_map.get_shield_guys()[i];
            shield_guy->set_shield();
        }
        passed_time = 0.0;
    }
}

void Game::init_texts()
{
    for (int i = 0; i < 3; i++)
    {
        Text temp;
        temp.setFont(this->font);
        temp.setColor(Color(0, 24, 89));
        temp.setStyle(Text::Style::Bold);
        texts.push_back(temp);
    }
}

void Game::init_font()
{
    if (!this->font.loadFromFile(LOBBY_FONT))
        cout << "ERROR: FAILED TO LOAD FONTS" << endl;
}

void Game::init_background()
{
    this->bg_texture = new Texture;
    if (!bg_texture->loadFromFile(BACKGROUND_IM))
        cout << "did not find background!" << endl;

    this->background.setTexture(*bg_texture);

    background.setScale(
        1.5 * this->game_map.get_screen().x / background.getGlobalBounds().width,
        2.5 * this->game_map.get_screen().y / background.getGlobalBounds().height);

    this->background.setOrigin(this->map_window->getSize().x / 2.f, this->map_window->getSize().y / 2.f + 250);
}

void Game::update_texts()
{

    texts[0].setPosition(view.getCenter().x - (view.getSize().x / 2) + 10, view.getCenter().y - (view.getSize().y / 2));
    texts[0].setString("Health: " + to_string(this->player.get_health()));

    texts[1].setPosition(view.getCenter().x - 25, view.getCenter().y - (view.getSize().y / 2));
    texts[1].setString("Score: " + to_string(this->player.get_score()));

    texts[2].setPosition(view.getCenter().x + (view.getSize().x / 2) - 75, view.getCenter().y - (view.getSize().y / 2));
    texts[2].setString("Baby: " + to_string(this->game_map.get_Babys().size()));
}
