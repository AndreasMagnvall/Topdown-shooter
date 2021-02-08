#ifndef Object_h_loaded
#define Object_h_loaded

#include <SFML/Graphics.hpp>
#include <memory>

/**
   Class responsible for handling all objects during play state.
   Keeps track of position, sprite and scale.
*/

/**
   Enum for each object type.
*/
enum obj_type{enemy = 0, player = 1, bullet = 2, wall_tile = 3, floor_tile = 4};

class Object
{
protected:
    bool collision{false};
    float scale_x{};
    float scale_y{};
    std::shared_ptr<sf::Vector2f> position{};
    std::shared_ptr<sf::Vector2f> size{};
    std::shared_ptr<sf::Texture> texture{};
    std::shared_ptr<sf::Sprite> sprite{};
    sf::RenderWindow* window;
    obj_type type;
    bool marked_delete{};
public:
    Object(std::shared_ptr<sf::Vector2f> position,
           std::shared_ptr<sf::Vector2f> size,
           std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window);
    virtual ~Object();

    /**
       Returns if the object is set to have collision
     */
    bool has_collision() const;
    /**
       Returns the objects collision
     */
    sf::Vector2f get_position() const;
    /**
       Sets the objects collision
     */
    sf::Vector2f set_position(sf::Vector2f new_position);
    /**
       Returns the objects Sprite object.
     */
    std::shared_ptr<sf::Sprite> get_sprite() const;
    /**
       Returns the objects Texture object.
     */
    std::shared_ptr<sf::Texture> get_texture() const;
    /**
       Returns the objects type.
     */
    obj_type get_type() const;

    /**
       Marks the object for deletion.
    */
    void set_marked_delete();
    /**
       Returns if the object is marked for deletion.
    */
    bool is_marked_delete() const;
    /**
       Draws the objects graphic on the associated window.
     */
    virtual void draw_object();
};

#endif
