#ifndef Character_h_loaded
#define Character_h_loaded

#include "Movable_Obj.h"

/**
   Object class responsible for representing a character. 
   Also handles some minor health mechanics.
*/
class Character : public Movable_Obj
{
protected:
    int hp;
public:
    Character(std::shared_ptr<sf::Vector2f> position,
              std::shared_ptr<sf::Vector2f> size,
              std::shared_ptr<sf::Texture>texture, sf::RenderWindow* window,
              std::string direction, int hp);

    /**
       Returns the characters current hp value.
     */
    int get_hp() const;
    /**
       Decreases the characters hp by the input damage.
     */
    void decrease_hp(int damage);
    /**
       Abstract function.
       Uses the function "prepare_move" or "prepare_move_to_obj".
     */
    virtual void move(std::vector<std::shared_ptr<Object>> collision_list) = 0;
};

#endif
