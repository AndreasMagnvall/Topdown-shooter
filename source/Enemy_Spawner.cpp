#include "Enemy_Spawner.h"

Enemy_Spawner::Enemy_Spawner(std::vector<std::shared_ptr<Movable_Obj>>& enemies, const Enemy& enemy,
                             int duration, int interval , sf::RenderWindow* window)
    : enemies{enemies}, enemy{enemy}, duration{duration}, interval{interval}, window{window}
{
    spawn_position.x = enemy.get_position().x;
    spawn_position.y = enemy.get_position().y;

    std::shared_ptr<Enemy> enemy1 = std::shared_ptr<Enemy>(
        new Enemy(std::shared_ptr<sf::Vector2f>(new sf::Vector2f(spawn_position)),
                  std::shared_ptr<sf::Vector2f>(new sf::Vector2f(20, 20)),
                  enemy.get_texture(), window, 3));
    enemies.push_back(enemy1);

    begin = std::chrono::steady_clock::now();
    begin_duration = std::chrono::steady_clock::now();
}

Enemy_Spawner::~Enemy_Spawner()
{}

void Enemy_Spawner::spawn_enemy()
{
    if(std::chrono::duration_cast<std::chrono::milliseconds>(
           std::chrono::steady_clock::now() - begin_duration).count()
       < duration)
    {
        if(std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin).count()
           > interval)
        {

            std::shared_ptr<Enemy> enemy1 = std::shared_ptr<Enemy>(
                new Enemy(std::shared_ptr<sf::Vector2f>(new sf::Vector2f(spawn_position)),
                          std::shared_ptr<sf::Vector2f>(new sf::Vector2f(20, 20)),
                          enemy.get_texture(), window, 3));
            enemies.push_back(enemy1);
            begin = std::chrono::steady_clock::now();
        }
    }
}

bool Enemy_Spawner::check_delete() const
{
    if(std::chrono::duration_cast<std::chrono::milliseconds>(
           std::chrono::steady_clock::now() - begin_duration).count()
       > duration)
    {
        return true;
    }
    return false;
}
