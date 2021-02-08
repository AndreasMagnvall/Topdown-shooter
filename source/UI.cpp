#include "UI.h"

UI::UI(sf::RenderWindow* window, std::string text, sf::Vector2f size, sf::Vector2f pos)
    : window(window), text(text), size(size), pos(pos)
{
    ui_rect = sf::RectangleShape(size);
    ui_rect.setPosition(pos);
    ui_rect.setFillColor(sf::Color(255, 255, 255));
  
    text_font.loadFromFile("./assets/FreeSerif.ttf");

    ui_text.setFont(text_font);
    ui_text.setCharacterSize(30);
    ui_text.setFillColor(sf::Color(0, 0, 0));
    ui_text.setPosition({ui_rect.getPosition().x + ui_rect.getSize().x/4, 
                ui_rect.getPosition().y + ui_rect.getSize().y/4});
}

UI::~UI()
{}

void UI::draw()
{
    ui_text.setString(text);
    window->draw(ui_rect);
    window->draw(ui_text);
}

void UI::draw_with_hp(int hp)
{
    ui_text.setString(text + std::to_string(hp));
    window->draw(ui_rect);
    window->draw(ui_text);
}
