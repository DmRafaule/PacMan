#include "GUI.hpp"
#include <iostream>

GUI::GUI(const bool *whichGUI){
   isMenu = whichGUI[0];
   isStartMenu = whichGUI[3];
   isBadEndGame = whichGUI[1];
   isGoodEndGame = whichGUI[2];
   if (isMenu){
      initMenu();
   }
   if (isBadEndGame || isGoodEndGame){
      initEndGame();
   }
   if (isStartMenu){
      initStartMenu();
   }
}
GUI::~GUI(){
      isMenu=false;
      isBadEndGame=false;
      isGoodEndGame=false;
      isStartMenu=false;
      delete texture;
      delete sprite;
      delete ss;
      delete posOnScreen;
      delete font;
      delete text;
}

void GUI::_update(const bool isGUI, sf::RenderTarget &win){
   if (isGUI){
      if (isMenu) updateMenu(win);
      if (isBadEndGame || isGoodEndGame) updateEndGame(win);
      if (isStartMenu) updateStartMenu(win);
   }
}
void GUI::updateEndGame(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;
    
   
   if (isBadEndGame) *ss << "\tGAME OVER\n\n\n\n\n\npress Enter to exit";
   if (isGoodEndGame) *ss << "\tGAME OVER but you WIN\n\tpress Enter to exit";
   text->setString(ss->str());
   ss->str("");
   
   if (isBadEndGame){//A little animation
      sprite->move(1,0);
      frame+=0.06;
      if (frame < 4) sprite->setTextureRect(sf::IntRect(50*static_cast<int>(frame),95,50,50));//Animation for rightward;
      else frame = 0;
      if (sprite->getGlobalBounds().left > win.getSize().x) sprite->setPosition(-50,0);
   }
   if (isGoodEndGame){ 
      sprite->setPosition(*posOnScreen);
      text->setPosition(posOnScreen->x+20,posOnScreen->y+250);
   }
   else    text->setPosition(posOnScreen->x-150,posOnScreen->y);
}
void GUI::updateMenu(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;
    
   *ss << "Menu\t\t\tHelp\n\nSettings\t\tQuit";
   text->setString(ss->str());
   ss->str("");
    
   sprite->setPosition(*posOnScreen);
   text->setPosition(posOnScreen->x + 100,
                     posOnScreen->y + 30);

}
sf::CircleShape& GUI::updateMenuArrow(){
   return *arrow;
}
const sf::Sprite& GUI::getMenuArrow() const{
   return *sprite;
}
void GUI::updateStartMenu(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;

   *ss << " Start\n\nSettings\n\n  Quit";
   text->setString(ss->str());
   ss->str("");

   sprite->setPosition(posOnScreen->x + 40,
                       posOnScreen->y - 200);
   text->setPosition(posOnScreen->x + 150,
                     posOnScreen->y);
}

void GUI::_render(sf::RenderTarget &win, const bool isGUI){
   if (isGUI){
      if (isMenu) renderMenu(win);
      if (isBadEndGame || isGoodEndGame) renderEndGame(win);
      if (isStartMenu) renderStartMenu(win);
   }
}
void GUI::renderEndGame(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
}
void GUI::renderMenu(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
   win.draw(*arrow);
}
void GUI::renderStartMenu(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
}

void GUI::initStartMenu(){
   texture = new sf::Texture();
   texture->loadFromFile("../texture/startMenu.jpg");
   sprite = new sf::Sprite(*texture);
   sprite->scale(0.5,0.5);
   ss = new std::stringstream();
   
   posOnScreen = new sf::Vector2f();
   
   font = new sf::Font();
   font->loadFromFile("../fonts/CodenameCoderFree4FBold.ttf");
   
   text = new sf::Text();
   text->setFont(*font);
   text->setFillColor(sf::Color::White);
   text->setCharacterSize(60);
   text->setStyle(sf::Text::Style::Bold);
   text->setOutlineColor(sf::Color::Blue);
   text->setOutlineThickness(1);
}
void GUI::initEndGame(){
   texture = new sf::Texture();
   if (isBadEndGame){
      texture->loadFromFile("../texture/pacman.png");
      sprite = new sf::Sprite(*texture);
      sprite->setTextureRect(sf::IntRect(0,0,50,50));
      sprite->setPosition(0,0);
   }
   if (isGoodEndGame){
      texture->loadFromFile("../texture/gameOver.png");
      sprite = new sf::Sprite(*texture);
      sprite->setScale(2,2);
   }

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

   arrow = new sf::CircleShape(20,3);
   arrow->setRotation(90);
   arrow->setPosition(200,320);
   arrow->setOutlineColor(sf::Color::Blue);
   arrow->setOutlineThickness(1);
   
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