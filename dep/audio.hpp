#pragma once 

#include <SFML/Audio.hpp>
/*

   This class provide a sounds and musics(obviosly)

*/


class Audio{
private:
   sf::SoundBuffer   *buffer;
   sf::Sound         *sound;
   bool              isMusic  = false;
   float             volume   = 1;
private:
public:
   void playSound();             //Play music
   void stopSound();             //For stop playing sound
   void loadSound(const char*);  //For loading sound
   void loopSound(bool isloop);  //Set up loop our sound or not
   Audio(float volume);          //Create a conteiners and set up volums
   ~Audio();
};