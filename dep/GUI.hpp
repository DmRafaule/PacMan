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

   float frame=0;

   bool isMenu = false;//Menu in game(when it start)
   bool isStartMenu = false;//Menu on the start game
   bool isBadEndGame = false;
   bool isGoodEndGame = false;
private:
   void initMenu();
   void initEndGame();
   void initStartMenu();
   
   void updateEndGame(sf::RenderTarget &win);
   void updateMenu(sf::RenderTarget &win);
   void updateStartMenu(sf::RenderTarget &win);

   void renderEndGame(sf::RenderTarget &win);
   void renderMenu(sf::RenderTarget &win);
   void renderStartMenu(sf::RenderTarget &win);
public:
   GUI(const bool*);
   ~GUI();
   void _update(const bool isGUI, sf::RenderTarget &win);
   void _render(sf::RenderTarget &win, const bool isGUI);
};


