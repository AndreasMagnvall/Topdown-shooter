#include "Game.h"

Game::Game()
{}

Game::~Game()
{}

void Game::run()
{
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window{desktop, "Game screen", sf::Style::Titlebar | sf::Style::Close};
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    std::map<std::string, State*> game_screens;

    game_screens["stage1"] = nullptr;
    game_screens["main_menu"] = new Menu_State(&window);

    std::string state{"main_menu"};

    sf::Clock clock;
    while(state.compare("EXIT") != 0){
        current_state = game_screens.at(state);
        sf::Event event;

        if(!current_state) //checks nullptr
        {
            current_state = new Play_State(&window);
            game_screens[state] = current_state;
        }

        if(state.compare("main_menu") == 0)
        {
            delete game_screens["stage1"];
            game_screens["stage1"] = nullptr;
        }

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        if(!window.isOpen())
        {
            return;
        }

        state = current_state->run_state();
        current_state->draw_screen();
    }

    window.close();
}
