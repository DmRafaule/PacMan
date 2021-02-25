#include "GUI.hpp"
#include <iostream>

GUI::GUI(const bool *whichGUI){
   isMenu=whichGUI[0];
   if (isMenu == true){
      initMenu();
   }

}

GUI::~GUI(){
   if (isMenu == true){
      isMenu=false;
      std::cout << "free memory"  << std::endl;
      delete texture;
      delete sprite;
      delete ss;
      delete posOnScreen;
      delete font;
      delete text;
   }
}

void GUI::_update(const bool isGUI, sf::RenderTarget &win){
   if (isGUI){
      if (isMenu) updateMenu(win);
   }
}
void GUI::updateEndGame(sf::RenderTarget &win){

}
void GUI::updateMenu(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;
    
   *ss << "Menu\t\tHelp\n\nSettings\tQuit";
   text->setString(ss->str());
   ss->str("");
    
   sprite->setPosition(*posOnScreen);
   text->setPosition(posOnScreen->x + 30,
                     posOnScreen->y + 30);
}
   
void GUI::_render(sf::RenderTarget &win, const bool isGUI){
   if (isGUI){
      if (isMenu) renderMenu(win);
   }
}
void GUI::renderEndGame(sf::RenderTarget &win){
   
}
void GUI::renderMenu(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
}
void GUI::initEndGame(){

}
void GUI::initMenu(){
   std::cout << "alloc mem"  << std::endl;
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
   text->setOutlineColor(sf::Color::Blue);
   text->setOutlineThickness(1);
}