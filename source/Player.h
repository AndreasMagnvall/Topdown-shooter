#ifndef Player_h_loaded
#define Player_h_loaded

#include <chrono>

#include "Character.h"
#include "Bullet.h"

/**Class responsible for some basic character functions and separating it from
other game objects */
class Player : public Character
{
private:
    bool invincible;
    std::chrono::steady_clock::time_point invincibility_begin;
    std::chrono::steady_clock::time_point shoot_time;
    int shoot_delay;
public:
    Player(std::shared_ptr<sf::Vector2f> position,
           std::shared_ptr<sf::Vector2f> size,
           std::shared_ptr<sf::Texture> texture,
           sf::RenderWindow* window, int hp);

    /**
       Returns true if the player is "invincible".
     */
    bool is_invincible() const;
    /**
       Set the invincibility status of the player.
     */
    void set_invincibility(bool status);
    /**
       Returns a string naming a direction based on keyboard input.
     */
    std::string check_input() const;
    /**
       Uses the function "prepare_move".
       Collision is checked with the objects in the vector collision_list.
     */
    void move(std::vector<std::shared_ptr<Object>> collision_list) override;
    /**
       Checks if the player should shoot and if so, creates a bullet object
       at the players position with the players angle and using the input 
       bullet_texture as its graphic.

       After "shooting" the bullet, places the bullet object in the 
       list object bullet_list.
     */
    void check_shoot(std::vector<std::shared_ptr<Movable_Obj>>* bullet_list, 
                     std::shared_ptr<sf::Texture> bullet_texture);
    /**
       Draws the player objects graphic on the associated window.

       Changes the color of the graphic depending on if the player
       is invincible or not.
     */
    void draw_object() override;
};

#endif
