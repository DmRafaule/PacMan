#ifndef PACK_E_HPP
#define PACK_E_HPP

/*
Class for handling other class and connect them (pack,ghost,Map, world)
*/


#include "pack.hpp"//Class about user and interacion with game session
#include "world.hpp"//Class about ghost map world titles points ...
#include "GUI.hpp"//Class about any kind of graphics user interfase in game (exeption is status bar in class pack(I'm just too lazy for recoding this))
#include "audio.hpp"


class Game{
private:
    sf::RenderWindow *window;
    sf::Event *event;
    
    Hero_pack *pack;
    World *world;
    Audio *audio;
    
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
    short isEndGame = 0;//Types of endings game
    bool whichGUI[5]{false};//[0] - menu in game session  
                            //[1] - bad end
                            //[2] - goog end
                            //[3] - main menu 
                            //[4] - help
    bool isGUI = true;//True if some gui are rendering
    bool isStartGame = false;//This tell that game is not start yet
    bool callOnce = true;//For allocate memmory only onse after player has reached any kind of endings game
public:
    
    void run();//main infinity loop
    void update();//timers and updating events and sfml events
    void render();//render all graphics
    
    Game();
    ~Game();
};

#endif
