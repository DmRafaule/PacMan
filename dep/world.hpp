#pragma once 
/*
This class will implement all related with world(ghost, map)
*/

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "map.hpp"
#include "ghost.hpp"



class World{

public:

    World(unsigned int winWidth, unsigned int winHeight, int optionMap);
    ~World();
    void _render(sf::RenderTarget &win);
    void _update(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack);
    
    /*Getters*/
    /*Return actual data about map*/
    std::vector<std::vector<sf::Sprite>> &_getTiles();
    /*Return actual data about ghost*/
    Ghost &_getGhost();

private:
    /*Init f*/
    void initVar(unsigned int winWidth, unsigned int winHeight);
    void initTiles();
    void initMap(int optionMap);
    void initGhost();
    
    /*Render f*/
    void renderMap(sf::RenderTarget &win);
    void renderGhost(sf::RenderTarget &win);
    /*update f*/
    void updateGhost(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack);
    void updateMap();
private:
    std::vector<std::vector<sf::Sprite>>    *tiles;
    sf::Texture                             *textureMap;
    sf::Texture                             *textureP;
    sf::Sprite                              *spriteMap;
    sf::Sprite                              *spriteP;

    unsigned int                            winHeight, winWidth;
private:    
    Map                                     *map;
    Ghost                                   *ghost;
};