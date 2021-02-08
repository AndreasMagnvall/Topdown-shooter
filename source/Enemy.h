#ifndef Enemy_h_loaded
#define Enemy_h_loaded

#include "Character.h"

/**
   Class responsible for representing an enemy 
   and separating it from the other game objects.
*/
class Enemy : public Character
{
public:
    Enemy(std::shared_ptr<sf::Vector2f> position,
          std::shared_ptr<sf::Vector2f> size,
          std::shared_ptr<sf::Texture> texture,
          sf::RenderWindow* window, int hp);

    /**
       Uses the function "prepare_move".
       Collision is checked with the objects in the vector collision_list.
     */
    void move(std::vector<std::shared_ptr<Object>> collision_list) override;
};

#endif
