#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iterator>
#include <map>

#include "Tile.h"
#include "Floor.h"
#include "Wall.h"
#include "Player.h"

/**
   GameMap class responsible for reading the map file and insertings it's values into
   the game. Primarly the the background tiles and player positin.
*/

class GameMap
{
private:
    /**
       Tile_Template struct working as a abstraction helper tool for parsing raw map
       into the game's map format. Only used inside GameMap class class.
    */
    struct Tile_Template
    {
        Tile_Template(int id, std::shared_ptr<sf::Texture> texture, bool is_wall, std::string texture_name);
        Tile_Template() = default;
        int id{};
        std::shared_ptr<sf::Texture> texture;
        std::string texture_name;
        bool is_wall{};
    };

    sf::RenderWindow* window;
    std::vector<std::vector<int>> int_map{};
    std::map<std::string, std::shared_ptr<sf::Texture>> textures{};
    std::map<int, Tile_Template> dict{};
    std::vector<std::shared_ptr<Tile>> tile_map;
    std::shared_ptr<Player> player_char;
public:
    GameMap(sf::RenderWindow* window);
    ~GameMap();

    /**
       Open and closes filestream and calling other map functions 
    */
    void read_map(std::string filename);
    /** 
        Reads player data from map file and translates them to game format.  
    */
    void read_player(std::ifstream& fs);
    /**
       Getter for player
    */
    std::shared_ptr<Player> get_player() const;
    /**
       Getter for tile map
    */
    std::vector<std::shared_ptr<Tile>> get_tile_map() const;
    /**
       Reads map coordinates and inserts earch type into a vector 
    */
    void get_map(std::ifstream& fs);
    /**
       Creates parsing rules for the map from a raw data to correct tile,
       defined later in map file 
    */
    void parse_map(std::ifstream& fs);
    /**
       Applies parsing rules to raw data list and creates a new list with correct
       tile data 
    */
    void insert_map();
};
