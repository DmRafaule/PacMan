#pragma once

/*
    Class about loading maps(levels)
    and return it world
*/

#include "SFML/Graphics.hpp"

class Map{
private:
    //Container for holding addresses
    const char *maps[4]{"../maps/map1.txt",
                        "../maps/map2.txt",
                        "../maps/map3.txt",
                        "../maps/map4.txt"};
    //Container for holding map
    sf::String map[24];
private:
    //Load map from txt file
    void load_map(const char *path);
public:
    Map(int optionMap);
    ~Map();
    //Returning character for class World
    const char get_map(size_t iterator_x,size_t itertor_y) const;
};