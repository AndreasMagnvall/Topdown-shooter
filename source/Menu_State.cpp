#include "Menu_State.h"

Menu_State::Menu_State(sf::RenderWindow* window)
    : State(window)
{
    text_font.loadFromFile("./assets/FreeSerif.ttf");

    sf::Text Menu1;
    Menu1.setFont(text_font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Start game");
    Menu1.setPosition({280.f, 160.f});
    menu_bars.push_back(Menu1);

    sf::Text Menu2;
    Menu2.setFont(text_font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Exit game");
    Menu2.setPosition({280.f, 220.f});
    menu_bars.push_back(Menu2);

    menu_select = 0;
}

Menu_State::~Menu_State()
{}

void Menu_State::draw_screen()
{
    window->clear();

    if(menu_select == 0)
    {
        menu_bars[0].setString("> Start game <");

        menu_bars[1].setString("    Exit game");
    }
    else if(menu_select == 1)
    {
        menu_bars[0].setString("    Start game");

        menu_bars[1].setString("> Exit game <");
    }

    for_each(menu_bars.begin(), menu_bars.end(), [this](sf::Text bar)
             {
                 window->draw(bar);
             });

    window->display();
}

std::string Menu_State::run_state()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
    }

    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        && menu_select > 0 )
    {
        menu_select--;
    }

    else if( (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
             || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
             && menu_select < (menu_bars.size()-1) )
    {
        menu_select++;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if(menu_select == 0)
        {
            return "stage1";
        }
        else if(menu_select == 1)
        {
            return "EXIT";
        }
    }

    return "main_menu";
}
