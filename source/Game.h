#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "State.h"
#include "Play_State.h"
#include "Menu_State.h"

/**
   The main class of the game, used for starting the game, controlling
   the game progression and finally ending the game.
 */
class Game
{
private:
    State* current_state;
public:
    Game();
    ~Game();

    /**
       Starts the game and runs it until the end.
     */
    void run();
};
