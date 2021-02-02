#pragma once 

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "map.hpp"

/*This class will implement all related with world(i.e. enemies, bg , interact , obj etc)*/


class World{

public:

    World(unsigned int winWidth, unsigned int winHeight);
    ~World();
    void _render(sf::RenderTarget &win);
    void _update();

private:
    /*Init f*/
    void initVar(unsigned int winWidth, unsigned int winHeight);
    void initTiles();
    void initMap();
    
    /*Render f*/
    void renderMap(sf::RenderTarget &win);

    /*update f*/
private:
    std::vector<std::vector<sf::Sprite>> tiles;
    sf::Texture textureMap;
    sf::Sprite spriteMap;

    unsigned int winHeight, winWidth;
private:
    Map *map;
};