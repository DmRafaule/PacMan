#pragma once 

#include <SFML/Graphics.hpp>
#include <sstream>

/* 

THIS is class for handling windows with text and some info for player
(exept a f-tion in class Hero_pack::updateStatus_Bar)

*/

class GUI{
private:
   sf::Texture       *texture;
   sf::Sprite        *sprite;
   std::stringstream *ss;
   sf::Font          *font;
   sf::Text          *text;
   sf::Vector2f      *posOnScreen;

   sf::CircleShape   *arrow;
   float             frame=0;

   bool              isMenu         = false;//Menu in game(when it start)
   bool              isStartMenu    = false;//Menu on the start game
   bool              isBadEndGame   = false;
   bool              isGoodEndGame  = false;
   bool              isHelp         = false;
   bool              isSettings     = false;
   float             volume         = 1;
   int               map            = 0;
private:
   /*Init gui*/
   void initMenu();
   void initEndGame();
   void initStartMenu();
   void initHelp();

   /*Update gui*/   
   void updateEndGame(sf::RenderTarget &win);
   void updateMenu(sf::RenderTarget &win);
   void updateStartMenu(sf::RenderTarget &win);
   void updateHelp(sf::RenderTarget &win);

   /*Render gui*/
   void renderEndGame(sf::RenderTarget &win);
   void renderMenu(sf::RenderTarget &win);
   void renderStartMenu(sf::RenderTarget &win);
   void renderHelp(sf::RenderTarget &win);

public:
   GUI(const bool*);//Make decision, which kind of gui it should be init
   ~GUI();//Make decision, what kind of memmory should be free 
   void _update(const bool isGUI, sf::RenderTarget &win);//Update only those who are picked constructor's or in pack_E.cpp
   void _render(sf::RenderTarget &win, const bool isGUI);//Render only those who are picked constructor's or in pack_E.cpp
public:   
   sf::CircleShape& getArrow();           //Return ref to arrow(in gui)
   const sf::Sprite& getMenu() const;     //Return ref to gui image
   void getVolume(const float *volume);   //For displaying volum in settings menu
   void getMap(const int *map);           //For displaying maps in settings menu
};


