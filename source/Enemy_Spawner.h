#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "Movable_Obj.h"

/**
   Class responsible for continuous spawn of enemies during a game session.
*/
class Enemy_Spawner
{
private:
    std::vector<std::shared_ptr<Movable_Obj>>& enemies;
    Enemy enemy;
    int duration;
    int interval;
    sf::RenderWindow* window;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point begin_duration;

    sf::Vector2f spawn_position;
public:
    Enemy_Spawner(std::vector<std::shared_ptr<Movable_Obj>>& enemies, const Enemy& enemy,
                  int duration, int interval, sf::RenderWindow* window);
    ~Enemy_Spawner();

    /**
       Creates an enemy at the spawners position.
    */
    void spawn_enemy();
    /**
       Returns if the enemy spawner should be deleted.
    */
    bool check_delete() const;
};
