#include "GUI.hpp"
#include <iostream>

GUI::GUI(const bool *whichGUI){
   this->isMenu = new bool;
   this->isStatusBar = new bool;

   *this->isMenu = whichGUI[0];
   *this->isStatusBar = whichGUI[1];

   if (*this->isMenu) initMenu();
   if (*this->isStatusBar) initStatusBar();
}

GUI::~GUI(){
   if (*this->isMenu || *this->isStatusBar){
      delete texture;
      delete sprite;
      delete posOnScreen;
      delete ss;
      delete font;
      delete text;
      
      if (*this->isMenu) delete menu;
   }
}

void GUI::_update(const bool isGUI, sf::RenderTarget &win){
   if (isGUI){
      if (*this->isMenu) menu->_update(win);
   }
}
void GUI::_render(sf::RenderTarget &win, const bool isGUI){
   if (isGUI){
      if (*this->isMenu) menu->_render(win);
   }
}

void GUI::initMenu(){
   texture = new sf::Texture();
   texture->loadFromFile("../texture/menu.png");
   sprite = new sf::Sprite(*texture);
   ss = new std::stringstream();
   
   posOnScreen = new sf::Vector2f();
   
   font = new sf::Font();
   font->loadFromFile("../fonts/CodenameCoderFree4FBold.ttf");
   
   text = new sf::Text();
   text->setFont(*font);
   text->setFillColor(sf::Color::White);
   text->setCharacterSize(40);
   text->setStyle(sf::Text::Style::Bold);
   text->setOutlineColor(sf::Color::Magenta);
   text->setOutlineThickness(1);

   menu = new Menu(*sprite,*ss,*posOnScreen,*text);
}
void GUI::initStatusBar(){

}