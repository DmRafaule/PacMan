#include "map.hpp"

Map::Map(){
    gen_map();
}
Map::~Map(){

}

const char Map::get_map(size_t i, size_t j) const{
    return map1[i][j];
}
char Map::gen_map(){

}