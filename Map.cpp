#include "Map.hpp"

const char GROUND = '.';
const char PORTAL = '$';
const char DIEHARD = 'E';
const char SHIELD = 'M';
const char BABY = 'O';
const char DIAMOND = '^';
const char STAR = '*';

const string GROUNDTXR = "Images/Ground.png";
const string DIAMONDTXR = "Images/diamond.png";
const string STARTXR = "Images/star.png";
const string DIRTTXR = "Images/Dirt.png";
const string PORTALTXR = "Images/portal.png";
const string DIEHARDTXR = "Images/shield/dont_set/0.png";
const string BABYTXR = "Images/boy/0.png";
const string SHIELDTXR = "Images/shield/dont_set/0.png";


const String BABY_FRAMES_ADDRESS = "Images/boy/";
const int BABY_FRAMENUM = 17;

const String SHIELD_GUY_FRAMES_ADDRESS = "Images/shield/set/";
const int SHIELD_GUY_FRAMENUM = 12;

const String ARMORED_SHIELD_GUY_FRAMES_ADDRESS = "Images/shield/dont_set/";
const int ARMORED_SHIELD_GUY_FRAMENUM = 12;

float const height = 20.0;
float const widht = 20.0;
float const gap = height;

// Private Functions
void MAP::init_texture()
{
    ground_texture = new Texture;
    if (!ground_texture->loadFromFile(GROUNDTXR))
        cout << "ERROR: couldnt find game_map -> ground_texture" << endl;
    dirt_texture = new Texture;
    if (!dirt_texture->loadFromFile(DIRTTXR))
        cout << "ERROR: couldnt find game_map -> dirt_texture" << endl;
    portal_texture = new Texture;
    if (!portal_texture->loadFromFile(PORTALTXR))
        cout << "ERROR: couldnt find game_map -> portal_texture" << endl;
    diamond_texture = new Texture;
    if (!diamond_texture->loadFromFile(DIAMONDTXR))
        cout << "ERROR: couldnt find game_map -> diamond_texture" << endl;
    star_texture = new Texture;
    if (!star_texture->loadFromFile(STARTXR))
        cout << "ERROR: couldnt find game_map -> star_texture" << endl;
    
}

MAP::MAP()
{
    init_texture();
    init_animations();
}

// animation method
void MAP::init_animation_frames(vector<Texture> *frames, string address, int max_frame)
{
    for (int i = 0; i < max_frame; i++)
    {
        Texture tmp;
        tmp.loadFromFile(address + to_string(i) + ".png");
        frames->push_back(tmp);
    }
}

void MAP::init_animations()
{
    init_animation_frames(&this->baby_frames, BABY_FRAMES_ADDRESS, BABY_FRAMENUM);
    init_animation_frames(&this->Shield_guy_frames, SHIELD_GUY_FRAMES_ADDRESS, SHIELD_GUY_FRAMENUM);
    init_animation_frames(&this->armored_shield_guy_frames, ARMORED_SHIELD_GUY_FRAMES_ADDRESS, ARMORED_SHIELD_GUY_FRAMENUM);
}

// Functions
void MAP::read_inputs(string file_name)
{
    vector<vector<char>> file_content;
    ifstream File(file_name);
    if (File.is_open())
    {
        std::string line;

        while (getline(File, line))
        {
            vector<char> chars(line.begin(), line.end());
            chars.push_back('\n');
            file_content.push_back(chars);
        }
        File.close();
    }
    else
        cout << "ERROR: game_map file_name didnt found" << endl;
    input = file_content;
}

void MAP::make_diamond(float cur_x, float cur_y, Texture *texture)
{
    RectangleShape diamond(Vector2f(15, 15));
    diamond.setTexture(texture);
    diamond.setPosition(cur_x, cur_y);
    diamonds.push_back(diamond);
}

void MAP::make_star(float cur_x, float cur_y, Texture *texture)
{
    RectangleShape star(Vector2f(15, 15));
    star.setTexture(texture);
    star.setPosition(cur_x, cur_y);
    stars.push_back(star);
}

void MAP::make_ground(float cur_x, float cur_y, Texture *texture)
{
    RectangleShape ground(Vector2f(height, widht));
    ground.setTexture(texture);
    ground.setPosition(cur_x, cur_y);
    grounds.push_back(ground);
}

void MAP::make_portal(float cur_x, float cur_y, Texture *texture)
{
    portal.setSize(Vector2f(60, 60));
    portal.setPosition(cur_x, cur_y - 40);
    portal.setTexture(texture);
}

void MAP::make_die_hard(float cur_x, float cur_y)
{
    Die_hard enemy(DIEHARDTXR, &this->Shield_guy_frames);
    enemy.to_pos(Vector2f(cur_x, cur_y)); //
    enemys.push_back(enemy);
}

void MAP::make_baby_turtle(float cur_x, float cur_y)
{
    Baby_turtle Baby(BABYTXR, &this->baby_frames);
    Baby.to_pos(Vector2f(cur_x, cur_y));
    baby_turtles.push_back(Baby);
}

void MAP::make_shield_guy(float cur_x, float cur_y)
{
    Shield_guy enemy(SHIELDTXR, &this->Shield_guy_frames, &this->armored_shield_guy_frames);
    enemy.to_pos(Vector2f(cur_x, cur_y)); 
    enemys.push_back(enemy);
    
    Shield_guy *temp = (Shield_guy *)(&enemys[enemys.size() - 1]);

    shieldGuys.push_back(temp);
}

void MAP::make_texture(char c, float &cur_x, float &cur_y)
{
    cur_x += widht;
    if (c == GROUND)
    {
        if (!is_top(cur_x, cur_y))
            make_ground(cur_x, cur_y, ground_texture);
        else
            make_ground(cur_x, cur_y, dirt_texture);
    }
    if (c == PORTAL)
    {
        make_portal(cur_x, cur_y, portal_texture);
    }
    if (c == DIEHARD)
    {
        make_die_hard(cur_x, cur_y);
    }
    if (c == SHIELD)
    {
        make_shield_guy(cur_x, cur_y);
    }
    if (c == BABY)
    {
        make_baby_turtle(cur_x, cur_y);
    }
    if (c == DIAMOND)
    {
        make_diamond(cur_x, cur_y, diamond_texture); 
    }
    if (c == STAR)
    {
        make_star(cur_x, cur_y, star_texture); 
    }
}

void MAP::make_map()
{
    float cur_y = 0.0;
    float cur_x;
    for (int i = 0; i < input.size(); i++)
    {
        cur_x = -widht;
        for (int j = 0; j < input[i].size(); j++)
        {
            make_texture(input[i][j], cur_x, cur_y);
        }
        cur_y += gap;
    }
}

void MAP::close()
{
    delete ground_texture;
    delete dirt_texture;
    delete portal_texture;
}

vector<RectangleShape> *MAP::get_ground()
{
    return &grounds;
}

float MAP::calculate_width()
{
    int max = 0;
    for (auto row : input)
    {
        if (row.size() >= max)
            max = row.size();
    }
    return max * widht;
}

float MAP::calculate_height()
{
    return input.size() * gap;
}

Vector2f MAP::get_screen()
{
    return Vector2f(calculate_width(), calculate_height());
}

bool MAP::is_in_map(Sprite sprite)
{
    if (sprite.getGlobalBounds().left <= 0.f ||
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= this->get_screen().x)
        return false;
    return true;
}

bool MAP::is_top(float x, float y)
{
    y -= gap;
    for (auto ground : grounds)
    {
        if (ground.getPosition().x == x && ground.getPosition().y == y)
            return true;
    }
    return false;
}

bool MAP::is_intersected(Sprite sprite, RectangleShape shape)
{
    if (sprite.getGlobalBounds().intersects(shape.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool MAP::did_it_hit(Sprite sprite, Person enemy)
{
    if (sprite.getGlobalBounds().intersects(enemy.get_sprite().getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool MAP::is_move_valid(Sprite sprite, vector<RectangleShape> *shapes)
{
    for (auto shape : *shapes)
    {
        if (is_intersected(sprite, shape))
        {
            return false;
        }
    }
    return true;
}

bool MAP::is_on_edge(Sprite sprite)
{
    float l_x = sprite.getPosition().x - sprite.getGlobalBounds().width / 2;
    float r_x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
    float space = 10.0; //
    float b_y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
    for (auto ground : grounds)
    {
        if (ground.getGlobalBounds().contains(l_x, b_y + space))
        {
            for (auto ground : grounds)
            {
                if (ground.getGlobalBounds().contains(r_x, b_y + space))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

RectangleShape MAP::get_portal()
{
    return portal;
}

vector<Enemy> &MAP::get_enemys()
{
    return enemys;
}

vector<Shield_guy *> &MAP::get_shield_guys()
{
    return shieldGuys;
}
