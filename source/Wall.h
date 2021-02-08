#ifndef Wall_h_loaded
#define Wall_h_loaded

#include "Tile.h"

/**
   Tile object representing a Wall with collision.
*/
class Wall : public Tile
{
public:
    Wall(std::shared_ptr<sf::Vector2f> position, 
         std::shared_ptr<sf::Vector2f> size, 
         std::shared_ptr<sf::Texture> texture,
         sf::RenderWindow* window);
};

#endif
