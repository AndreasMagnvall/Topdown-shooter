#include "Movable_Obj.h"

Movable_Obj::Movable_Obj(std::shared_ptr<sf::Vector2f> position,
                         std::shared_ptr<sf::Vector2f> size,
                         std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window, std::string direction)
    : Object(position, size, texture, window), direction(direction)
{}

sf::Vector2f Movable_Obj::get_last_pos() const
{
    return last_pos;
}

void Movable_Obj::set_last_pos(sf::Vector2f new_pos)
{
    last_pos = new_pos;
}

std::string Movable_Obj::get_direction() const
{
    return this->direction;
}

void Movable_Obj::set_direction(std::string new_direction)
{
    this->direction = new_direction;
}

std::vector<double> Movable_Obj::prepare_move(std::string direction, double speed, bool is_dir_locked)
{
    std::vector<double> mvm_xy(2);

    if(direction.compare("up") == 0)
    {
        mvm_xy[1] -= speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(270.0f);
            this->direction = "up";
        }
    }
    else if(direction.compare("left") == 0)
    {
        mvm_xy[0] -= speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(180.0f);
            this->direction = "left";
        }
    }
    else if(direction.compare("right") == 0)
    {
        mvm_xy[0] += speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(0.0f);
            this->direction = "right";
        }
    }
    else if(direction.compare("down") == 0)
    {
        mvm_xy[1] += speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(90.0f);
            this->direction = "down";
        }
    }
    else if(direction.compare("up-left") == 0)
    {
        double diagonal_speed = speed / std::sqrt(2);
        mvm_xy[0] -= diagonal_speed;
        mvm_xy[1] -= diagonal_speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(235.0f);
            this->direction = "up-left";
        }
    }
    else if(direction.compare("up-right") == 0)
    {
        double diagonal_speed = speed / std::sqrt(2);
        mvm_xy[0] += diagonal_speed;
        mvm_xy[1] -= diagonal_speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(315.0f);
            this->direction = "up-right";
        }
    }
    else if(direction.compare("down-left") == 0)
    {
        double diagonal_speed = speed / std::sqrt(2);
        mvm_xy[0] -= diagonal_speed;
        mvm_xy[1] += diagonal_speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(135.0f);
            this->direction = "down-left";
        }
    }
    else if(direction.compare("down-right") == 0)
    {
        double diagonal_speed = speed / std::sqrt(2);
        mvm_xy[0] += diagonal_speed;
        mvm_xy[1] += diagonal_speed;

        if(!is_dir_locked)
        {
            sprite->setRotation(45.0f);
            this->direction = "down-right";
        }
    }
    return mvm_xy;
}

std::vector<double> Movable_Obj::prepare_move_to_obj(std::shared_ptr<Object> target_obj, double speed)
{
    double angle_to_target = atan2(target_obj->get_position().y - position->y,
                                   target_obj->get_position().x - position->x);
    angle_to_target *= 57;
    angle_to_target += 90;

    while( angle_to_target > 360 )
    {
        angle_to_target -= 360;
    }

    while( angle_to_target < 0 )
    {
        angle_to_target += 360;
    }

    if( angle_to_target > 25 && angle_to_target < 65 )
    {
        return prepare_move("up-right", speed);
    }
    else if( angle_to_target >= 65 && angle_to_target <= 115 )
    {
        return prepare_move("right", speed);
    }
    else if( angle_to_target > 115 && angle_to_target < 155 )
    {
        return prepare_move("down-right", speed);
    }
    else if( angle_to_target >= 155 && angle_to_target <= 205 )
    {
        return prepare_move("down", speed);
    }
    else if( angle_to_target > 205 && angle_to_target < 245 )
    {
        return prepare_move("down-left", speed);
    }
    else if( angle_to_target >= 245 && angle_to_target <= 295 )
    {
        return prepare_move("left", speed);
    }
    else if( angle_to_target > 295 && angle_to_target < 335 )
    {
        return prepare_move("up-left", speed);
    }
    else
    {
        return prepare_move("up", speed);
    }
}
