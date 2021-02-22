#pragma once 

#include <array>
#include <SFML/Graphics.hpp>

class Ghost{
public:
    Ghost();
    ~Ghost();
    void __update(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack);
    void __render();
    void setPos(float x, float y);//set position of each ghost
    sf::Sprite &_getGhostSprite();
    void showStat();//TEMP REMOVE NOW!!!
private:
    /*Init f-tions*/
    //init ghost
    void initTexture();
    //init ghost eyes
    void initVision();
    //init time 
    void initTime();
    /*Update f-tions*/
        /*About movements*/
        /*f-tions for movements*/
        void updateMovements();
            //f-tion for changing of direction if ghost dont see pack(usual behavior2)
            void updateMovementsNoVisionPack();
                /*For detect a walls*/
                bool updateCollisionWalls();
                //f-tion for make desision which direction to choose
                int updateDecision();
                    //This one defined which way ghost could go
                    int defineOptions(sf::FloatRect sens[]);
            //f-tion for changing of direction if ghost can see pack
            void updateMovementsYesVisionPack();
            //How we change a directions
            void updateChangingMovements();
            //Correcting position of ghost for "square moves(i.e. turning by angle 90deg and fix positon)"
            void updateCorrectMovements();
            //for detection pack
            void updateVisionPack();
        //for interact with map
        void updateTiles(std::vector<std::vector<sf::Sprite>> &tiles);
        //for interact with pac
        void updatePack(sf::Sprite &pack);
        //update info about window
        void updateWin(sf::RenderTarget &win);
        //for correct displaying eyes on ghost
        void updateVision();
        //for timers and time
        void updateTime();
        //for updating animation
        void updateAnimation();

private:
    // texture sprite time clock packPos
    /*For knowing by ghost where tiles and pack are*/
    std::vector<std::vector<sf::Sprite>> *tiles;
    sf::Sprite *pack;
    sf::RenderTarget *win;
    //Timer
    sf::Clock *clock;
    sf::Time time;

    sf::Texture *texture;
    sf::Sprite *sprite;
    sf::RectangleShape *vision;//for detcting a surroundig on distanse//NOW IT'S OFF
    enum Colors:int{//Type of ghost
        red,
        green,
        blue,
        yellow
    };
    sf::Vector2f packPos;//for remember a coordinate of pack
private:
    bool isRight=true,isLeft=false,isTop=false,isBottom=false;//for directions of  moves
    bool left_s = true,right_s = true,top_s = true,bottom_s = true;//Sensors for define free ways
    bool wherePack[4]{false};//for detecting pack
    bool fixPos=true;//this is need for correct position only once(look at updateCorrectMovements())
    bool isFirst=true;//This is for touching a wall only once
    float dir_x = 0;//speed of ghost on OX
    float dir_y = 0;//speed of ghost on OY
    float frame = 0;//for animation
    int outcome;//It's for contain a answer about which way to choose
};