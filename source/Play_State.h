#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <chrono>

#include "State.h"
#include "Tile.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameMap.h"
#include "UI.h"
#include "Enemy_Spawner.h"
#include "Movable_Obj.h"

/**
   State class responsible for managing a playtrough of a game session.
*/
class Play_State : public State
{
private:
    std::shared_ptr<UI> hp_bar;
    std::shared_ptr<Enemy_Spawner> enemy_spawner;
    std::shared_ptr<Player> player_char;
    std::shared_ptr<sf::Texture> bullet_texture;
    std::vector<std::shared_ptr<Movable_Obj>> movable_objects;
    std::vector<std::shared_ptr<Tile>> map;
    std::vector<std::shared_ptr<Enemy_Spawner>> spawners;
    int player_speed;
    bool p_pressed;
    std::string temp_return;

    /**
       Runs the process of each enemy spawner.
    */
    void spawn_enemies();
    /**
       Runs the process of each movable object.
    */
    void move_objects();
    /**
       Creates and draws a UI object containing the text
       described by the input msg.
    */
    void popup(std::string msg);
    /**
       Runs the process of checking if the player has won or lost.

       Creates and draws a UI object with a message depending
       on if the player won or lost.
    */
    std::string check_win_lose();
    /**
       Returns the amount of enemies in the object list.
    */
    int enemy_amount() const;
public:
    /**
       Play_State constructor.
       - stores the RenderWindow.
       - creates a hp bar UI object.
       - loads textures used in play_state.
       - creates enemies as spawn templates.
       - creates some enemy spawners using the spawn templates.
     */
    Play_State(sf::RenderWindow* window);
    ~Play_State();

    /**
       Draws one frame of the play_state on the screen.
       Uses the sprite of the player and all the floors, walls,
       enemies and bullets.
    */
    void draw_screen() override;
    /**
       Progresses the game one tick.
    */
    std::string run_state() override;
};
