#include "Character.h"

Character::Character(std::shared_ptr<sf::Vector2f> position, 
                         std::shared_ptr<sf::Vector2f> size, 
                         std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window, std::string direction, int hp)
    : Movable_Obj(position, size, texture, window, direction), hp(hp)
{}

int Character::get_hp() const
{
    return this->hp;
}

void Character::decrease_hp(int damage)
{
    this->hp -= damage;
}

