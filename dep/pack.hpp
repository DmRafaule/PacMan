#ifndef PACK_HPP
#define PACK_HPP

/*
Class about packman(player) and interaction with world, enemies
*/

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Hero_pack{
private:
    sf::Texture texture;
    sf::Sprite pack;
    float dir_x=0, dir_y=0;
    void collisions(sf::Event &, sf::RenderTarget &);//for detecting  a border of screen
    void movements(sf::Event &);//f-tion for movements
    void ch_movements(sf::Event &);//f-tion for changing of direction 
    void correct_movements(float &dir_x, float &dir_y);//f-tion for smooth movement(i.e. right angles )
public:
    Hero_pack();//init character pack
    void _render(sf::RenderTarget *);//for render on main window
    void _update(sf::Event &, sf::RenderTarget &);//for all updating events to pack
};

#endif