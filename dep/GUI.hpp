#pragma once 

#include <SFML/Graphics.hpp>
#include <sstream>
#include "menu.hpp"

class GUI{
private:
   sf::Texture *texture;
   sf::Sprite *sprite;
   
   std::stringstream *ss;
   sf::Font *font;
   sf::Text *text;

   sf::Vector2f *posOnScreen;

   Menu *menu;

   bool *isMenu,*isStatusBar;
private:
   void initMenu();
   void initStatusBar();
public:
   GUI(const bool*);
   ~GUI();
   void _update(const bool isGUI, sf::RenderTarget &win);
   void _render(sf::RenderTarget &win, const bool isGUI);
};


