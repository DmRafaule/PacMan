#pragma once 


#include <SFML/Graphics.hpp>

class Ghost{
public:
    Ghost();
    ~Ghost();
    void __update(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack);
    void __render(sf::RenderTarget &win);
    void setPos(float x, float y);//set position of each ghost
    sf::Sprite &_getGhostSprite();
    void showStat();//TEMP REMOVE NOW!!!
private:
    void initTexture();//init ghost
    void initVision();//init ghost eyes
        /*about collisions*/
    void collisions(sf::RenderTarget &);//for detecting  a border of screen
    void collisionBorders(sf::RenderTarget &);
    void collisionWalls(sf::RenderTarget &);
    
    /*about movements*/
    void movements(sf::Sprite &pack);//f-tion for movements
    void ch_movements(sf::Sprite &pack);//f-tion for changing of direction 
    void correct_movements();//correcting if pack visable
    
    void visionPack(sf::Sprite &pack);//for detection pack
    
    void updateTiles(std::vector<std::vector<sf::Sprite>> &tiles);//for inteact with map
    void updateVision();//for correct displaying eyes on ghost
    void updateTime();//for timers and time
    void updateAnimation();//for updating animation
    
private:
    std::vector<std::vector<sf::Sprite>> *tiles;
    sf::Sprite *pack;
    sf::RenderTarget *win;

    sf::Clock clock;
    sf::Time time;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape *vision;//for detcting a surroundig on distanse
    enum Colors:int{//types of ghost
        red,
        green,
        blue,
        yellow
    };
    float frame = 0;
private:
    bool isRight=false,isLeft=false,isTop=false,isBottom=false;
    bool isFirst=true;//this is need for correct a move only once since they have see a packman or they just stop
    bool isWall=false;
    float dir_x = 0;
    float dir_y = 0;
    int posPac_x;
    int posPac_y;
};