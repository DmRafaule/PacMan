#pragma once 

#include <SFML/Audio.hpp>
/*

   This class provide a sounds and musics(obiosly)

*/


class Audio{
private:
   sf::SoundBuffer *buffer;
   sf::Sound *sound;
   bool isMusic = false;
private:
public:
   void playSound();
   void stopSound();
   void loadSound(const char*);
   Audio();
   ~Audio();
};