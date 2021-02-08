#pragma once

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

class Map{
private:
    sf::String map1[12]{{"__########___#__"},
                       {"___________#_#_#"},
                       {"_##_###_##_#___#"},
                       {"_##_#_#_#__#_#_"},
                       {"____#_____##_#__"},
                       {"#_##_#_###_#_____"},
                       {"#_##_#_#_#_###___"},
                       {"_____###_#_____#_"},
                       {"__#_##_____###_#_"},
                       {"__#____#_#_____#"},
                       {"__###_##_#######_"},
                       {"______#__________"}};
private:
    char gen_map();//TODO
public:
    const char get_map(size_t iterator_x,size_t itertor_y) const;
    Map();
    ~Map();
};