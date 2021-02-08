#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>

#include "State.h"

/**
   State class responsible for handling the main menu.
 */
class Menu_State : public State
{
private:
    sf::Font text_font;
    std::vector<sf::Text> menu_bars;
    int menu_select;
public:
    Menu_State(sf::RenderWindow* window);
    ~Menu_State();

    /**
       Draws one frame of the menu on the screen.
       The menu consists of text objects which are drawn.
     */
    void draw_screen() override;
    /**
       Progresses the menu state one tick.
     */
    std::string run_state() override;
};
