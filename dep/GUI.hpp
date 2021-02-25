#pragma once 

#include <SFML/Graphics.hpp>
#include <sstream>
#include "menu.hpp"


// THIS is class for handling windows with text and some info for player
//(exept a f-tion in class Hero_pack::updateStatus_Bar)

class GUI{
private:
   sf::Texture *texture;
   sf::Sprite *sprite;
   std::stringstream *ss;
   sf::Font *font;
   sf::Text *text;
   sf::Vector2f *posOnScreen;

   bool isMenu = false;
   bool isEndGame = false;
private:
   void initMenu();
   void initEndGame();
   
   void updateEndGame(sf::RenderTarget &win);
   void renderEndGame(sf::RenderTarget &win);
   void updateMenu(sf::RenderTarget &win);
   void renderMenu(sf::RenderTarget &win);
public:
   GUI(const bool*);
   ~GUI();
   void _update(const bool isGUI, sf::RenderTarget &win);
   void _render(sf::RenderTarget &win, const bool isGUI);
};


