#include "Tile.h"

Tile::Tile(std::shared_ptr<sf::Vector2f> position, 
           std::shared_ptr<sf::Vector2f> size, 
           std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window)
    : Object(position, size, texture, window)
{}
