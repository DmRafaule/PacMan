#ifndef PACK_E_HPP
#define PACK_E_HPP

/*
Class for handling other class and connect them (pack, ghost, map, world, audio)
*/


#include "pack.hpp"
#include "world.hpp"
#include "GUI.hpp"
#include "audio.hpp"


class Game{
private:
    sf::RenderWindow    *window;
    sf::Event           *event;
    
    Hero_pack           *pack;
    World               *world;
    Audio               *audio;
    
    GUI                 *gui;


    /*Game time*/
    sf::Clock           globalClock;
    sf::Time            globalTime;
    /*Options*/
    float               optionVolume=1;
    int                 optionMap=0;/*which map to load from 0 to 3*/
private:
    enum TypeOfEnd{
        NOT_END,
        BAD_END,
        GOOD_END
    };
    short               isEndGame = 0;//Types of endings game
    bool                whichGUI[6]{false};//[0] - menu in game session  
                                           //[1] - bad end
                                           //[2] - goog end
                                           //[3] - main menu 
                                           //[4] - help
                                           //[5] - settings
    bool isGUI       = true;//True if some gui are rendering
    bool isStartGame = false;//This tell that game is not start yet
    bool callOnce    = true;//For allocate memmory only onse after player has reached any kind of endings game
public:
    
    void run();//main infinity loop
    void update();//timers and updating events and sfml events
    void render();//render all graphics
    
    Game();
    ~Game();
};

#endif
