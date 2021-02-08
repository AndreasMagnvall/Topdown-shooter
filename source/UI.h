#ifndef UI_h_loaded
#define UI_h_loaded

#include <SFML/Graphics.hpp>

/**
   Class used for creating a rectangle object containing text.
   Used for message boxes.
 */
class UI
{
private:
    sf::RenderWindow* window;
    sf::RectangleShape ui_rect;
    sf::Text ui_text;
    std::string text;
    sf::Vector2f size;
    sf::Vector2f pos;
    sf::Font text_font;
public:
    UI(sf::RenderWindow* window, std::string text, sf::Vector2f size, sf::Vector2f pos);
    ~UI();

    /**
       Draws the UI objects components (rectangle and text).
     */
    void draw();
    /**
       Draws the UI objects components, but adds the input hp
       to the end of the text.

       Currently used for writing player hp.
     */
    void draw_with_hp(int hp);
};

#endif
