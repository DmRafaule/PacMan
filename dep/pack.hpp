#ifndef PACK_HPP
#define PACK_HPP

/*
Class about packman(player) and interaction with world, enemies
*/

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "ghost.hpp"

class Hero_pack{
private:
    /*For holding info about map*/
    std::vector<std::vector<sf::Sprite>> *tiles;
    /*For holdig info about globalTime*/
    sf::Clock *clock;
    sf::Time *localTime;

    /*For pack textures*/
    sf::Texture texture;
    sf::Sprite pack;
    /*For status bar*/
    sf::Texture *texture_bar;
    sf::Sprite *sprite_bar;
    sf::Font *font;
    sf::Text *textScore,*textHealth;
    
    /*for directions of moves*/
    float dir_x = 0, dir_y = 1;
    /*for status bar*/
    int score = 0, sizeHealthBar = 6;
    float frame = 0;
    char *healthBar;//contain ****** as default
    bool isWall=false;//logical(it isn't wall)
    bool isBar=false;//about question of existing status bar
    bool isGhost=false;//for detect a ghost
private: 
    /*INIT F.*/
    /*about some actions(like pop up score,health,settings or do something else)*/
    void initStatus_Bar(sf::Event &);
    /*UPDATE F.*/
    /*for detecting  a border of screen*/
    void updateCollisions(sf::RenderTarget &, Ghost &);
        /*For detect colisions with border of screen*/
        void updateCollisionBorders(sf::RenderTarget &);
        /*For detect colisions with tiles(walls) and points*/
        void updateCollisionWallsPoint(sf::RenderTarget &);
        /*For detect collisions with ghost*/
        void updateCollisionGhost(Ghost &);

    /*for detecting a key input and make some moves*/
    void updateMovements(sf::Event &);
        /*f-tion for changing of direction*/
        void updateCh_movements(sf::Event &);
        /*f-tion for smooth movement(i.e. right angles )*/
        void updateCorrect_movements(float &dir_x, float &dir_y);
    /*update state of tiles map*/
    void updateTiles(std::vector<std::vector<sf::Sprite>> &tiles);
    /*update state of status bar*/
    void updateStatus_Bar(sf::RenderTarget &window, sf::Time &globalTime);
    /*update local time*/
    void updateTime();
    short updateEndGame();
    void updateAnimation();
public:
    /*init character pack*/
    Hero_pack();
    ~Hero_pack();
    /*for Ghosts (they have to know where pack is)*/
    sf::Sprite &_getPack();
    /*for render on main window*/
    void _render(sf::RenderTarget *);
    /*for all updating events to pack*/
    void _update(sf::Event &, sf::RenderTarget &, std::vector<std::vector<sf::Sprite>> &, Ghost &,sf::Time &globalTime, short& isEndGame);
};

#endif