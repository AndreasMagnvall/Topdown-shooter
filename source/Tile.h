#ifndef Tile_h_loaded
#define Tile_h_loaded

#include "Object.h"

/**
   Tile class used to represent an unmoveable part of the map.
*/
class Tile : public Object
{
public:
    Tile(std::shared_ptr<sf::Vector2f> position,
         std::shared_ptr<sf::Vector2f> size,
         std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window);
};

#endif
