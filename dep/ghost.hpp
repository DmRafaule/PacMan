#pragma once 

#include <array>
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
    /*Init f-tions*/
    //init ghost
    void initTexture();
    //init ghost eyes
    void initVision();
    /*Update f-tions*/
        /*about collisions*/
        void updateCollisions(sf::RenderTarget &);//for detecting  a border of screen
            /*For detect a walls*/
            bool updateCollisionWalls(sf::RenderTarget &);

        /*About movements*/
        /*f-tions for movements*/
        void updateMovements(sf::Sprite &pack);
            //f-tion for changing of direction if ghost dont see pack(usual behavior2)
            void updateMovementsNoVisionPack(sf::Sprite &pack);
                //f-tion for make desision which direction to choose
                int  updateDecision();/*split this function on initSensors checkSensors outcomeSensors repeatesOutcome*/
            //f-tion for changing of direction if ghost can see pack
            void updateMovementsYesVisionPack();
            //How we change a directions
            void updateChangingMovements();
            //Correcting position of ghost for "square moves(i.e. turning by angle 90deg and fix positon)"
            void updateCorrectMovements();
            //for detection pack
            void updateVisionPack(sf::Sprite &pack);
        //for inteact with map
        void updateTiles(std::vector<std::vector<sf::Sprite>> &tiles);
        //for correct displaying eyes on ghost
        void updateVision();
        //for timers and time
        void updateTime();
        //for updating animation
        void updateAnimation();

private:
    /*For knowing by ghost where tiles and pack are*/
    std::vector<std::vector<sf::Sprite>> *tiles;
    sf::Sprite *pack;
    sf::RenderTarget *win;
    //Timer
    sf::Clock clock;
    sf::Time time;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape *vision;//for detcting a surroundig on distanse
    enum Colors:int{//Type of ghost
        red,
        green,
        blue,
        yellow
    };
    sf::Vector2f packPos;//for remember a coordinate of pack
private:
    bool isRight=false,isLeft=false,isTop=true,isBottom=false;//for directions of  moves
    bool wherePack[4]{false};//for detecting pack
    bool fixPos=true;//this is need for correct position only once(look at updateCorrectMovements())
    bool isWall;//this is neen for detect a walls
    bool isFirst=true;//This is for touching a wall only once
    float dir_x = 0;//speed of ghost on OX
    float dir_y = 0;//speed of ghost on OY
    float frame = 0;//for animation
    int outcome;//It's for contain a answer about which way to choose
    int option,k=0;//DEL
};