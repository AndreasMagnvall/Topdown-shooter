#include "GameMap.h"

GameMap::Tile_Template::Tile_Template(int id, std::shared_ptr<sf::Texture> texture, bool is_wall, std::string texture_name)
    : id{id}, texture{texture}, is_wall{is_wall}, texture_name{texture_name}
{}

GameMap::GameMap(sf::RenderWindow* window)
    : window{window}
{}

GameMap::~GameMap()
{}

std::shared_ptr<Player> GameMap::get_player() const
{
    return player_char;
}

std::vector<std::shared_ptr<Tile>> GameMap::get_tile_map() const
{
    return tile_map;
}

void GameMap::read_map(std::string filename)
{
    std::ifstream fs;

    try
    {
        fs.open(filename);

        get_map(fs);
        parse_map(fs);
        insert_map();
        read_player(fs);
        fs.close();
    }
    catch(const std::exception& ex)
    {
        throw std::invalid_argument("Missing or invalid map file");
    }
}

void GameMap::get_map(std::ifstream& fs)
{
    char head[100];
    int c{};

    for (std::string temp; std::getline(fs, temp); )
    {
        if(temp.rfind("map:") == 0)
        {
            continue;
        }

        else if(temp.rfind("endmap:") == 0)
        {
            return;
        }
        else
        {
            int_map.push_back(std::vector<int>());
            std::for_each(temp.begin(),temp.end(),[this,&c](char x)
                          {
                              if(x != ',')
                              {
                                  int_map[c].push_back(x - '0');
                              }
                          });
            c++;
        }
    };
}

void GameMap::parse_map(std::ifstream& fs)
{
    int id{-1};
    std::shared_ptr<sf::Texture> texture;
    bool is_wall{};
    std::string test{};
    int colon{};
    std::string line{};
    std::string texture_name{};
    for (std::string temp; std::getline(fs, temp); )
    {
        if(temp.empty())
            continue;

        line = temp;

        colon = line.find(":");

        if(temp == "player:")
        {
            dict[id] = Tile_Template(id, texture, is_wall, texture_name);
            return;
        }
        else if(temp.rfind("id:") == 0)
        {
            line.erase(0,colon+1);
            if(id != -1)
            {
                dict[id] = Tile_Template(id, texture, is_wall, texture_name);
            }
            id = std::stoi(line);
        }
        else if(temp.rfind("texture:") == 0)
        {
            line = line.substr(colon+2);
            if(textures.empty())
            {
                texture = std::make_shared<sf::Texture>();
                texture->loadFromFile(line);
                texture_name = line;
                textures[texture_name] = texture;
            }
            else if(textures.find(line) == textures.end())
            {
                texture = std::make_shared<sf::Texture>();
                texture->loadFromFile(line);
                texture_name = line;
                textures[texture_name] = texture;
            }
            else
            {
                auto search = textures.find(line);
                texture = search->second;
                texture_name = line;
                textures[texture_name] = texture;
            }
        }
        else if(temp.rfind("iswall") == 0)
        {
            line = line.substr(colon+2);

            is_wall = line == "true" ? true : false;
        }
    }
}

void GameMap::insert_map()
{
    int x{};
    int y{-120};
    int j{};
    std::shared_ptr<Tile> temp;
    std::shared_ptr<sf::Texture> texture;
    for(auto v : int_map)
    {
        x = 0;
        for(int i : v)
        {

            texture = textures[dict[i].texture_name];

            if(dict[i].is_wall)
            {
                temp = std::shared_ptr<Wall>
                    (new Wall(
                        std::shared_ptr<sf::Vector2f>(new sf::Vector2f(x, y)),
                        std::shared_ptr<sf::Vector2f>(new sf::Vector2f(120, 120)),
                        texture, window));
            }
            else
            {
                temp = std::shared_ptr<Floor>
                    (new Floor(
                        std::shared_ptr<sf::Vector2f>(new sf::Vector2f(x, y)),
                        std::shared_ptr<sf::Vector2f>(new sf::Vector2f(120, 120)),
                        texture, window));
            }
            x += 120;
            tile_map.push_back(temp);
        };
        y += 120;
    };

}

void GameMap::read_player(std::ifstream& fs)
{
    std::string line{};
    int colon{};
    double positionx, positiony;
    int hp;
    std::shared_ptr<sf::Texture> texture;
    for (std::string temp; std::getline(fs, temp); )
    {
        line = temp;
        colon = line.find(":");
        line = line.substr(colon+2);
        if(temp.rfind("player:") == 0)
        {
            continue;
        }
        else if(temp.rfind("positionx:") == 0)
        {
            positionx = stod(line);
        }
        else if(temp.rfind("positiony:") == 0)
        {
            positiony = stod(line);

        }
        else if(temp.rfind("texture:") == 0)
        {
            texture = std::make_shared<sf::Texture>();
            texture->loadFromFile(line);
        }
        else if(temp.rfind("hp:") == 0)
        {
            hp = stoi(line);
            player_char = std::shared_ptr<Player>
                (new Player(std::shared_ptr<sf::Vector2f>(new sf::Vector2f(positionx, positiony)),
                            std::shared_ptr<sf::Vector2f>(new sf::Vector2f(20, 20)),
                            texture, window, hp));
            return;
        }
    }
}
