#include "Player.h"

Player::Player(std::shared_ptr<sf::Vector2f> position,
               std::shared_ptr<sf::Vector2f> size,
               std::shared_ptr<sf::Texture> texture,
               sf::RenderWindow* window, int hp)
    : Character(position, size, texture, window, "right", hp), invincible(false)
{
    invincibility_begin = std::chrono::steady_clock::now();
    shoot_time = std::chrono::steady_clock::now();
    shoot_delay = 0;

    type = player;
}

bool Player::is_invincible() const
{
    return invincible;
}

void Player::set_invincibility(bool status)
{
    invincible = status;
}

std::string Player::check_input() const
{
    std::string result_dir{""};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        result_dir = "up";
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            result_dir = "up-left";
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            result_dir = "up-right";
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        result_dir = "down";
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            result_dir = "down-left";
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            result_dir = "down-right";
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // no need to check for down-left/up-left at this point
        result_dir = "left";
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // no need to check for down-right/up-right at this point
        result_dir = "right";
    }
    return result_dir;
}

void Player::check_shoot(std::vector<std::shared_ptr<Movable_Obj>>* bullet_list, std::shared_ptr<sf::Texture> bullet_texture)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(shoot_delay > 30 &&
            std::chrono::duration_cast<std::chrono::milliseconds>
           (std::chrono::steady_clock::now() - shoot_time).count() > 500)
        {
            (*bullet_list).push_back(
                std::shared_ptr<Bullet>(
                    new Bullet(std::shared_ptr<sf::Vector2f>(
                                   new sf::Vector2f(get_position().x,
                                                    get_position().y)),
                               std::shared_ptr<sf::Vector2f>(
                                   new sf::Vector2f(5, 5)),
                               bullet_texture,
                               window,
                               get_direction()
                        )));
            shoot_time = std::chrono::steady_clock::now();
        }
    }
}

void Player::move(std::vector<std::shared_ptr<Object>> collision_list)
{
    shoot_delay++;

    if( std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - invincibility_begin).count()
        > 2000 )
    {
        set_invincibility(false);
    }

    std::vector<double> mvm_xy{};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        mvm_xy = prepare_move(check_input(), 2,
                              sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
        
        position->x += mvm_xy[0];
        position->y += mvm_xy[1];
    }

    std::vector<std::shared_ptr<Object>>::iterator obj_iter;
    for(obj_iter = collision_list.begin(); obj_iter != collision_list.end(); obj_iter++)
    {
        if(get_sprite()->getGlobalBounds().intersects(
               (*obj_iter)->get_sprite()->getGlobalBounds())
           && (*obj_iter)->has_collision() == true
           && (*obj_iter)->get_type() == wall_tile)
        {
            set_position(get_last_pos());
        }

        if(get_sprite()->getGlobalBounds().intersects(
               (*obj_iter)->get_sprite()->getGlobalBounds())
           && (*obj_iter)->get_type() == enemy
           && get_hp() > 0
           && !is_invincible())
        {
            decrease_hp(1);
            set_invincibility(true);
            invincibility_begin = std::chrono::steady_clock::now();
        }
    }
    set_last_pos(get_position());
}

void Player::draw_object()
{
    if( is_invincible() )
    {
        sprite->setColor(sf::Color(255, 255, 255, 100));
    }
    else
    {
        sprite->setColor(sf::Color(0, 0, 0, 255));
    }

    window->draw(*sprite);
}
