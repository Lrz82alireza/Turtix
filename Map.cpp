#include "Map.hpp"

const char Ground = '.';
const string GROUNDTXR = "Images/Ground.png";
const string DIRTTXR = "Images/Dirt.png";
float const height = 50.0;
float const widht = 20.0;
float const gap = height;

// Private Functions
void MAP::init_texture()
{
    ground_texture = new Texture;
    if(!ground_texture->loadFromFile(GROUNDTXR))
        cout << "ERROR: couldnt find map -> ground_texture" << endl;
    dirt_texture = new Texture;
    if(!dirt_texture->loadFromFile(DIRTTXR))
        cout << "ERROR: couldnt find map -> dirt_texture" << endl;
}

MAP::MAP()
{  
    init_texture();
}

// Functions
void MAP::read_inputs(string file_name)
{
    vector<vector<char>> file_content;
    ifstream File(file_name);
    if (File.is_open()) {
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
        cout << "ERROR: map file_name didnt found" << endl;
    input = file_content;
}

void MAP::make_ground(float cur_x , float cur_y , Texture * texture)
{
    RectangleShape ground(Vector2f(height , widht));
    ground.setTexture(texture);
    ground.setPosition(cur_x , cur_y);
    //ground.setFillColor(sf::Color::Green);
    grounds.push_back(ground);
}

void MAP::make_map()
{
    float cur_y = 0.0;
    float cur_x = 0.0;

    for (int i = 0 ; i < input.size() ; i++)
    {
        cur_x = -widht;
        for (int j = 0 ; j < input[i].size() ; j++)
        {
            if (input[i][j] == Ground)
            {
                cur_x += widht;
                if (!is_top(cur_x , cur_y))
                    make_ground(cur_x , cur_y , ground_texture);
                else
                    make_ground(cur_x , cur_y , dirt_texture);
            }
            else
                cur_x += widht;
        }
        cur_y += gap;
    }
}

vector <RectangleShape> MAP::get_ground()
{
    return grounds;
}

float MAP::calculate_widht()
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
    return input.size()*gap;
}

VideoMode MAP::get_screen()
{
    return VideoMode(calculate_widht() , calculate_height());
}

bool MAP::is_top(float x , float y)
{
    y -= gap;
    for(auto ground: grounds)
    {
        if (ground.getPosition().x == x && ground.getPosition().y == y)
            return true;
    }
    return false;
}

bool MAP::is_intersected(Sprite & sprite , RectangleShape &shape)
{
    if (sprite.getGlobalBounds().top < (shape.getGlobalBounds().top + shape.getGlobalBounds().height))
        return true;     
    
    if ((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) > shape.getGlobalBounds().top)
        return true;
    
    if (sprite.getGlobalBounds().left < (shape.getGlobalBounds().left + shape.getGlobalBounds().width))
        return true;
    
    if ((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) > shape.getGlobalBounds().left)
        return true;
    return false;
}

bool MAP::is_move_valid(Sprite &sprite , vector<RectangleShape>&shapes)
{
    for (auto shape : shapes)
    {
        if (is_intersected(sprite , shape))
            return false;
    }
    return true;
}