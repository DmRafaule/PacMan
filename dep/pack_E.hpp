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
    enum TypeOfEnd{
        NOT_END,
        BAD_END,
        GOOD_END
    };
    short isEndGame = 0;//Types of end game
    bool whichGUI[5]{false};//[0] - MENU  
                            //[1] - bad end
                            //[2] - goog end  
    bool isGUI = true;
    bool isStartGame = false;
    bool callOnce = true;//For allocate memmory  in stage game end
public:
    
    void run();//main infinity loop
    void update();//timers and updating events and sfml events
    void render();//render all graphics
    
    Game();
    ~Game();
};

#endif
