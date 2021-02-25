#include "GUI.hpp"
#include <iostream>

GUI::GUI(const bool *whichGUI){
   isMenu = whichGUI[0];
   isEndGame = whichGUI[1];
   if (isMenu){
      initMenu();
   }
   if (isEndGame){
      initEndGame();
   }
}

GUI::~GUI(){
   if (isMenu){
      isMenu=false;
      delete texture;
      delete sprite;
      delete ss;
      delete posOnScreen;
      delete font;
      delete text;
   }
   if (isEndGame){
      isEndGame=false;
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
      if (isEndGame) updateEndGame(win);
   }
}
void GUI::updateEndGame(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;
    
   
   
   *ss << "\tGAME OVER\n\n\n\n\n\npress Enter to exit";
   text->setString(ss->str());
   ss->str("");
   
   //A little animation
   sprite->move(1,0);
   frame+=0.06;
   if (frame < 4) sprite->setTextureRect(sf::IntRect(50*static_cast<int>(frame),95,50,50));//Animation for rightward;
   else frame = 0;
   if (sprite->getGlobalBounds().left > win.getSize().x) sprite->setPosition(-50,0);

   text->setPosition(posOnScreen->x-150,posOnScreen->y);
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
      if (isEndGame) renderEndGame(win);
   }
}
void GUI::renderEndGame(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
}
void GUI::renderMenu(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
}
void GUI::initEndGame(){
   texture = new sf::Texture();
   texture->loadFromFile("../texture/pacman.png");
   sprite = new sf::Sprite(*texture);
   sprite->setTextureRect(sf::IntRect(0,0,50,50));
   sprite->setPosition(0,0);

   ss = new std::stringstream();
   
   posOnScreen = new sf::Vector2f();
   
   font = new sf::Font();
   font->loadFromFile("../fonts/CodenameCoderFree4FBold.ttf");
   
   text = new sf::Text();
   text->setFont(*font);
   text->setCharacterSize(40);
   text->setStyle(sf::Text::Style::Bold);
   text->setOutlineColor(sf::Color::Blue);
   text->setOutlineThickness(2);
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
   text->setOutlineColor(sf::Color::Blue);
   text->setOutlineThickness(1);
}