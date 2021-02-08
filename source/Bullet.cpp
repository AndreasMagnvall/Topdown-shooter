#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet(std::shared_ptr<sf::Vector2f> position,
               std::shared_ptr<sf::Vector2f> size,
               std::shared_ptr<sf::Texture> texture,
               sf::RenderWindow* window, std::string direction)
    : Movable_Obj(position, size, texture, window, direction)
{
    type = bullet;

    float factor_x = window->getSize().x / 40.0 / window->getSize().x;
    float factor_y = window->getSize().y / 40.0 / window->getSize().y;
    sprite->setScale(factor_x, factor_y);
}

void Bullet::move(std::vector<std::shared_ptr<Object>> collision_list)
{
    std::vector<double> mvm_xy{prepare_move(direction, 10)};
    //bool wall_collided{false};

    position->x += mvm_xy[0];
    position->y += mvm_xy[1];

    std::vector<std::shared_ptr<Object>>::iterator obj_iter;
    for(obj_iter = collision_list.begin(); obj_iter != collision_list.end(); obj_iter++)
    {
        if(get_sprite()->getGlobalBounds().intersects(
               (*obj_iter)->get_sprite()->getGlobalBounds())
           && (*obj_iter)->has_collision() == true
           && (*obj_iter)->get_type() == wall_tile)
        {
            marked_delete = true;
            return;
        }

        if(get_sprite()->getGlobalBounds().intersects(
               (*obj_iter)->get_sprite()->getGlobalBounds())
           && (*obj_iter)->get_type() == enemy)
        {
            //collision_list.erase(obj_iter--);
            std::dynamic_pointer_cast<Enemy>(*obj_iter)->decrease_hp(1);

            if(std::dynamic_pointer_cast<Enemy>(*obj_iter)->get_hp() < 1)
            {
                std::dynamic_pointer_cast<Enemy>(*obj_iter)->set_marked_delete();
            }

            marked_delete = true;
            return;
        }
    }
}
