#ifndef Bullet_h_loaded
#define Bullet_h_loaded

#include <string>

#include "Object.h"
#include "Movable_Obj.h"

/**
   Movable_Obj class responsible for representing the bullet which
   the player character fires.
*/
class Bullet : public Movable_Obj
{
public:
    Bullet(std::shared_ptr<sf::Vector2f> position,
           std::shared_ptr<sf::Vector2f> size,
           std::shared_ptr<sf::Texture> texture,
           sf::RenderWindow* window, std::string direction);

    /**
       Uses the function "prepare_move".
       Collision is checked with the objects in the vector collision_list.
     */
    void move(std::vector<std::shared_ptr<Object>> collision_list) override;
};

#endif
