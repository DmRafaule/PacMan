#pragma once 


#include <SFML/Graphics.hpp>

class Ghost{
public:
    Ghost();
    ~Ghost();
    void __update(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack);
    void __render(sf::RenderTarget &win);
    void setPos(float x, float y);//set position of each ghost
    void showStat();//TEMP REMOVE NOW!!!
private:
    void initTexture();//init ghost
    void initEyes();//init ghost eyes
        /*about collisions*/
    void collisions(sf::RenderTarget &);//for detecting  a border of screen
    void collisionBorders(sf::RenderTarget &);
    void collisionWalls(sf::RenderTarget &);
    
    /*about movements*/
    void movements(sf::Sprite &pack);//f-tion for movements
    void ch_movements(sf::Sprite &pack);//f-tion for changing of direction 
    void correct_movements();//f-tion for smooth movement(i.e. right angles )
    
    void vision(sf::Sprite &pack);//for get an information about surroundings
    void updateTiles(std::vector<std::vector<sf::Sprite>> &tiles);//for inteact with map
    void updateEyes();//for correct displaying eyes on ghost
private:
    std::vector<std::vector<sf::Sprite>> *tiles;
    sf::Sprite *pack;
    sf::RenderTarget *win;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape *eyes;//for detcting a surroundig on distanse
    enum Colors:int{//types of ghost
        red,
        green,
        blue,
        yellow
    };
private:
    bool isRight=false,isLeft=false,isTop=true,isBottom=false;
    bool isFirst=true;
    float dir_x = 0;
    float dir_y = 0;
};