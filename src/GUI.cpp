#include "GUI.hpp"

GUI::GUI(const bool *whichGUI){
   isMenu = whichGUI[0];
   isStartMenu = whichGUI[3];
   isBadEndGame = whichGUI[1];
   isGoodEndGame = whichGUI[2];
   isHelp = whichGUI[4];
   isSettings = whichGUI[5];
   
   if (isMenu){
      initMenu();
   }
   if (isBadEndGame || isGoodEndGame){
      initEndGame();
   }
   if (isStartMenu){
      initStartMenu();
   }
   if (isHelp){
      initHelp();
   }
}
GUI::~GUI(){     
      delete texture;
      delete sprite;
      delete ss;
      delete posOnScreen;
      delete font;
      delete text;
      if (isMenu || isStartMenu) delete arrow;
      
      isMenu         =  false;
      isBadEndGame   =  false;
      isGoodEndGame  =  false;
      isStartMenu    =  false;
      isHelp         =  false;
      isSettings     =  false;
}

void GUI::_update(const bool isGUI, sf::RenderTarget &win){
   if (isGUI){
      if (isMenu)                         updateMenu(win);
      if (isBadEndGame || isGoodEndGame)  updateEndGame(win);
      if (isStartMenu)                    updateStartMenu(win);
      if (isHelp)                         updateHelp(win);
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
   //it should executing only once
   if (arrow->getPosition().x < text->getPosition().x && arrow->getPosition().y < text->getPosition().y)
      arrow->setPosition(text->getPosition().x - 15,text->getPosition().y + 10);// 15 and 10 it's value of neccessary shift(not good calculation)
}                                                                               // this is neccessary put them here because  I want interact with menu imediatly
sf::CircleShape& GUI::getArrow(){
   return *arrow;
}
const sf::Sprite& GUI::getMenu() const{
   return *sprite;
}
void GUI::getVolume(const float *volume){
   this->volume = *volume;
}
void GUI::getMap(const int *map){
   this->map = *map;
}
void GUI::updateStartMenu(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;

   if (isSettings){
      *ss << "Maps\t\t"<< map <<"\n\nVolume\t\t" << volume <<"\n\nBack to menu";
      text->setString(ss->str());
      ss->str("");
   }
   else{
      *ss << " Start\n\nSettings\n\n  Quit";
      text->setString(ss->str());
      ss->str("");
   }

   sprite->setPosition(posOnScreen->x + 40,
                       posOnScreen->y - 200);
   text->setPosition(posOnScreen->x + 150,
                     posOnScreen->y);
   //it should executing only once
   if (arrow->getPosition().x < text->getPosition().x && arrow->getPosition().y < text->getPosition().y)
      arrow->setPosition(text->getPosition().x,text->getPosition().y);
}
void GUI::updateHelp(sf::RenderTarget &win){
   posOnScreen->x = win.getSize().x/2 - sprite->getGlobalBounds().width/2;
   posOnScreen->y = win.getSize().y/2 - sprite->getGlobalBounds().height/2;


   *ss << "Arrows\t\t\t for moves\nTab\t\t\t\tfor open status\nQ\t\t\t\t  for close status\nEsc\t\t\t\tfor open menu\nWin\t\t\t\t600 poins";
   text->setString(ss->str());
   *ss <<"\n\n\n\n\n\n\nPress escape for close this help";
   text->setString(ss->str());
   ss->str("");
   sprite->setPosition(*posOnScreen);
   text->setPosition(posOnScreen->x + 100,
                     posOnScreen->y + 40);
}

void GUI::_render(sf::RenderTarget &win, const bool isGUI){
   if (isGUI){
      if (isMenu)                         renderMenu(win);
      if (isBadEndGame || isGoodEndGame)  renderEndGame(win);
      if (isStartMenu)                    renderStartMenu(win);
      if (isHelp)                         renderHelp(win);
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
   win.draw(*arrow);
}
void GUI::renderHelp(sf::RenderTarget &win){
   win.draw(*sprite);
   win.draw(*text);
}


void GUI::initStartMenu(){
   texture = new sf::Texture();
   texture->loadFromFile("../texture/startMenu.jpg");
   sprite = new sf::Sprite(*texture);
   sprite->scale(0.5,0.5);

   arrow = new sf::CircleShape(40,3);
   arrow->setRotation(90);
   arrow->setOutlineColor(sf::Color::Blue);
   arrow->setOutlineThickness(1);

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
void GUI::initHelp(){
   texture = new sf::Texture();
   texture->loadFromFile("../texture/menu.png");
   sprite = new sf::Sprite(*texture);
   sprite->setScale(1.32,3);
 
   ss = new std::stringstream();
   
   posOnScreen = new sf::Vector2f();

   font = new sf::Font();
   font->loadFromFile("../fonts/CodenameCoderFree4FBold.ttf");
   
   text = new sf::Text();
   text->setFont(*font);
   text->setFillColor(sf::Color::White);
   text->setCharacterSize(40);
}
