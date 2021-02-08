#ifndef Movable_obj_h_loaded
#define Movable_obj_h_loaded

#include "Object.h"
#include <string>
#include <cmath>

/**
   Object class used to represent a movable object. Has move functionality.
 */
class Movable_Obj : public Object
{
protected:
    std::string direction;
    sf::Vector2f last_pos;
    /**
       Made to use in the function "move".
       Returns a vector containing the x and y coordinates the
       object should be moved, also changes the variable "direction"
       if is_dir_locked equals false.
    */
    std::vector<double> prepare_move(std::string direction, double speed, bool is_dir_locked = false);
    /**
       Similar to "prepare_move".
       Moves the object towards the Object target_obj.
    */
    std::vector<double> prepare_move_to_obj(std::shared_ptr<Object> target_obj, double speed);
public:
    Movable_Obj(std::shared_ptr<sf::Vector2f> position,
                std::shared_ptr<sf::Vector2f> size,
                std::shared_ptr<sf::Texture>texture, sf::RenderWindow* window,
                std::string direction);

    /**
       Abstract function.
       Uses the function "prepare_move" or "prepare_move_to_obj".
     */
    virtual void move(std::vector<std::shared_ptr<Object>> collision_list) = 0;
    /**
       Returns the objects current direction.
     */
    std::string get_direction() const;
    /**
       Sets the objects current direction.
     */
    void set_direction(std::string new_direction);
    /**
       Gets the objects position before any collision has occured.
     */
    sf::Vector2f get_last_pos() const;
    /**
       Sets the variable last_pos to a new position.
       Should be used to set the objects position before
       any collision has occured.
     */
    void set_last_pos(sf::Vector2f new_pos);
};

#endif
