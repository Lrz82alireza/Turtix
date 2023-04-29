#include "Map.hpp"

const char Ground = '.';
const string GROUNDTXR = "Images/Ground.png";
float const height = 100.0;
float const weight = 100.0;
float const gap = 400.0;

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
    input = file_content;
}

void MAP::set_window(RenderWindow * init_window)
{
    window = init_window;
}

void MAP::make_ground(float cur_x , float cur_y , Texture * texture)
{
    RectangleShape ground(Vector2f(height , weight));
    ground.setTexture(texture);
    ground.setPosition(cur_x , cur_y);
    //ground.setFillColor(sf::Color::Green);
    grounds.push_back(ground);
}

void MAP::make_map()
{
    float cur_y = 0.0;
    float cur_x = 0.0;

    Texture ground;
    if(!ground.loadFromFile(GROUNDTXR))
    {
        abort();
    }
    
    for (int i = 0 ; i < input.size() ; i++)
    {
        cur_x = 0.0;
        for (int j = 0 ; j < input[i].size() ; j++)
        {
            if (input[i][j] == Ground)
            {
                make_ground(cur_x , cur_y , &ground);
                cur_x += weight;
            }
            else
                cur_x += weight;
        }
        cur_y += gap;
    }
}

vector <RectangleShape> MAP::get_ground()
{
    return grounds;
}