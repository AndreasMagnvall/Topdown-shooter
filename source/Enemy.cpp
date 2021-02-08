#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<sf::Vector2f> position,
             std::shared_ptr<sf::Vector2f> size,
             std::shared_ptr<sf::Texture> texture,
             sf::RenderWindow* window, int hp)
    : Character(position, size, texture, window, "right", hp)
{
    collision = true;
    type = enemy;
}

void Enemy::move(std::vector<std::shared_ptr<Object>> collision_list)
{
    std::vector<double> mvm_xy{};
    //bool wall_collided{false};

    std::vector<std::shared_ptr<Object>>::iterator obj_iter;
    for(obj_iter = collision_list.begin(); obj_iter != collision_list.end(); obj_iter++)
    {
        if((*obj_iter)->get_type() == player)
        {
            mvm_xy = prepare_move_to_obj((*obj_iter), 1);
            break;
        }
    }

    position->x += mvm_xy[0];
    position->y += mvm_xy[1];

    for(obj_iter = collision_list.begin(); obj_iter != collision_list.end(); obj_iter++)
    {
        if(get_sprite()->getGlobalBounds().intersects(
               (*obj_iter)->get_sprite()->getGlobalBounds())
           && (*obj_iter)->has_collision() == true
           && (*obj_iter)->get_type() == wall_tile)
        {
            set_position(get_last_pos());
        }
    }
    set_last_pos(get_position());
}
