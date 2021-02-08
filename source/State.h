#ifndef State_h_loaded
#define State_h_loaded

#include <SFML/Graphics.hpp>
#include <string>

/**
   Abstract base class for the games menu and play-states.
   Used by the game object to switch between screens.
*/
class State
{
protected:
    sf::RenderWindow* window;
public:
    State(sf::RenderWindow* window);
    virtual ~State();

    /**
       Draws one frame of the state on the screen.
    */
    virtual void draw_screen() = 0;
    /**
       Progresses the state one tick.
    */
    virtual std::string run_state() = 0;
};

#endif
