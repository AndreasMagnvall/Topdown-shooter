#include "Object.h"

Object::Object(std::shared_ptr<sf::Vector2f> position,
               std::shared_ptr<sf::Vector2f> size,
               std::shared_ptr<sf::Texture> texture, sf::RenderWindow* window)
    : position{position}, size{size}, texture{texture}, window{window}
{
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(*texture);

    float factor_x = window->getSize().x / 8.0 / window->getSize().x;
    float factor_y = window->getSize().y / 8.0 / window->getSize().y;
    sprite->setScale(factor_x, factor_y);

    sprite->setPosition(*position);
    sprite->setOrigin(texture->getSize().x/2,texture->getSize().y/2);
}

Object::~Object()
{}

bool Object::is_marked_delete() const
{
    return marked_delete;
}

bool Object::has_collision() const
{
    return collision;
}

std::shared_ptr<sf::Sprite> Object::get_sprite() const
{
    sprite->setPosition(*position);
    return sprite;
}

sf::Vector2f Object::get_position() const
{
    return *position;
}

sf::Vector2f Object::set_position(sf::Vector2f new_position)
{
    *position = new_position;
}

std::shared_ptr<sf::Texture> Object::get_texture() const
{
    return texture;
}

obj_type Object::get_type() const
{
    return type;
}

void Object::set_marked_delete()
{
    marked_delete = true;
}

void Object::draw_object()
{
    window->draw(*sprite);
}
