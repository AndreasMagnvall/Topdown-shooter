#include "Play_State.h"

Play_State::Play_State(sf::RenderWindow* window)
    : State(window)
{
    hp_bar = std::shared_ptr<UI>(new UI(window, "ammo: inf, hp: ", {400.0f, 50.0f}, {800.0f, 0.0f}));

    GameMap game_map(window);
    game_map.read_map("./assets/map.txt");
    map = game_map.get_tile_map();

    player_char = game_map.get_player();
    movable_objects.push_back(player_char);

    std::shared_ptr<sf::Texture> enemy_texture{new sf::Texture};
    enemy_texture->loadFromFile("./assets/devil.png");

    Enemy enemy1 = Enemy(std::shared_ptr<sf::Vector2f>(new sf::Vector2f(200, 200)),
                  std::shared_ptr<sf::Vector2f>(new sf::Vector2f(20, 20)),
                  enemy_texture, window, 1);

    Enemy enemy2 = Enemy(std::shared_ptr<sf::Vector2f>(new sf::Vector2f(1400, 200)),
                  std::shared_ptr<sf::Vector2f>(new sf::Vector2f(20, 20)),
                  enemy_texture, window, 1);

    enemy_spawner = std::make_shared<Enemy_Spawner>(Enemy_Spawner(movable_objects, enemy1, 5000, 1000, window));
    spawners.push_back(enemy_spawner);
    spawners.push_back(std::make_shared<Enemy_Spawner>(movable_objects, enemy2, 5000, 1000, window));

    bullet_texture = std::shared_ptr<sf::Texture>(new sf::Texture);
    bullet_texture->loadFromFile("./assets/boolet.png");

    player_speed = 200;
    p_pressed = false;
}

Play_State::~Play_State()
{}

void Play_State::draw_screen()
{
    std::vector<std::shared_ptr<Object>> drawable_objects;
    drawable_objects.insert(drawable_objects.begin(), movable_objects.begin(), movable_objects.end());
    drawable_objects.insert(drawable_objects.begin(), map.begin(), map.end());

    window->clear();
    for_each(drawable_objects.begin(), drawable_objects.end(), [this](std::shared_ptr<Object> obj)
             {
                 obj->draw_object();
             });
    hp_bar->draw_with_hp(player_char->get_hp());

    window->display();
}

int Play_State::enemy_amount() const
{
    int result{0};
    for(std::shared_ptr<Object> obj : movable_objects)
    {
        if(obj->get_type() == enemy)
        {
            result++;
        }
    }
    return result;
}

void Play_State::spawn_enemies()
{
    for(unsigned int i{0}; i < spawners.size();++i)
    {
        if(spawners[i] != nullptr)
        {
            spawners[i]->spawn_enemy();

            if(spawners[i]->check_delete())
            {
                spawners[i].reset();
                spawners.erase(spawners.begin()+i);
            }
        }
    }
}

void Play_State::move_objects()
{
    std::vector<std::shared_ptr<Object>> coll_objects;
    coll_objects.insert(coll_objects.begin(), movable_objects.begin(), movable_objects.end());
    coll_objects.insert(coll_objects.begin(), map.begin(), map.end());

    std::vector<std::shared_ptr<Movable_Obj>>::iterator obj_iter;
    for(obj_iter = movable_objects.begin(); obj_iter != movable_objects.end(); obj_iter++)
    {
        (*obj_iter)->move(coll_objects);
        if((*obj_iter)->is_marked_delete())
        {
            (*obj_iter).reset();
            movable_objects.erase(obj_iter--);
        }
    }
}

void Play_State::popup(std::string msg )
{
    UI message(window, msg + " \npress the \"Enter\" button \nto return to the main menu",
               {1000.0f, 400.0f}, {400.0f, 200.0f});

    window->clear();
    draw_screen();
    message.draw();
    window->display();
}

std::string Play_State::check_win_lose()
{
    std::string msg{};
    if(enemy_amount() < 1)
    {
        msg =  "You won!";
    }
    else if(player_char->get_hp() < 1)
    {
        hp_bar->draw_with_hp(player_char->get_hp());
        msg = "Game Over!";
    }
    if(msg.size() > 0)
    {
        popup(msg);

        bool enter_pressed{false};
        while(true)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                enter_pressed = true;
            }

            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
               && enter_pressed)
            {
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window->close();
                return "EXIT";
            }
        }
        return "main_menu";
    }

    return "";
}

std::string Play_State::run_state()
{
    spawn_enemies();

    temp_return = check_win_lose();
    if(temp_return.compare("") != 0)
    {
        return temp_return;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        p_pressed = true;
        player_speed = 0;
    }

    move_objects();

    if(p_pressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        popup("Game Paused");
        while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window->close();
                return "EXIT";
            }
        }
        p_pressed = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
    }

    player_char->check_shoot(&movable_objects, bullet_texture);

    return "stage1";
}
