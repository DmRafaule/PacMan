#ifndef PACK_E_HPP
#define PACK_E_HPP
/*
Class for handling other class and connect them (Hero_pack,Enemy_goust,Map)
*/


#include "pack.hpp"
#include "world.hpp"
#include "GUI.hpp"

class Game{
private:
    sf::RenderWindow *window;
    sf::Event *event;
    
    Hero_pack *pack;//Class about user and interacion with game
    World *world;
    GUI *gui;

    /*Game time*/
    sf::Clock globalClock;
    sf::Time globalTime;
private:
    bool isGUI = false;
    bool whichGUI[2]{false};//It's array for contain which screen is rendering
                            //[0] for menu
                            //[1] for status bar
public:
    
    void run();//main infinity loop
    void update();//timers and updating events and sfml events
    void render();//render all graphics
    
    Game();
    ~Game();
};

#endif
