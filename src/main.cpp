#include <ctime>
#include "pack_E.hpp"

/*
Just start game. Nothing interesting.
*/

int main(){
    srand(time(0));
    Game packman;
    packman.run();
    return 0;
}
