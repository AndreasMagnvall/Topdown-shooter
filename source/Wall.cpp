#include "Wall.h"

Wall::Wall(std::shared_ptr<sf::Vector2f> position, 
           std::shared_ptr<sf::Vector2f> size, 
           std::shared_ptr<sf::Texture> texture,
           sf::RenderWindow* window)
    : Tile(position, size, texture, window)
{
    type = wall_tile;
    collision = true;
}
