#ifndef Floor_h_loaded
#define Floor_h_loaded

#include "Tile.h"

/**
   Tile object representing a floor tile without collision.
 */
class Floor : public Tile
{
public:
    Floor(std::shared_ptr<sf::Vector2f> position,
          std::shared_ptr<sf::Vector2f> size,
          std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window);
};

#endif
