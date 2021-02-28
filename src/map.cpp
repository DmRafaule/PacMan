#include "map.hpp"

Map::Map(){
    load_map(maps[2]);
}
Map::~Map(){

}

const char Map::get_map(size_t i, size_t j) const{
    return map[i][j];
}
void Map::load_map(const char *path){//I know c style, but I know how to do this well on c .. so
    FILE  *fs;
    char buffer[100];
    int iterator = 0;
    if (fs = fopen(path,"r")){
        while (fgets(buffer,100,fs)){
            map[iterator] = buffer; 
            iterator++;
        }
    }
    else printf("error load map %s\n",path);
}