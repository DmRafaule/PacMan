#include "audio.hpp"


Audio::Audio(float volume){
   buffer = new sf::SoundBuffer;
   sound = new sf::Sound;
   sound->setVolume(volume);
}
Audio::~Audio(){
   delete buffer;
   delete sound;
}

void Audio::loadSound(const char* path){
   if (!isMusic){//if right now music not play we load in buffer new stuff
      buffer->loadFromFile(path);
      sound->setBuffer(*buffer);
   }
}
void Audio::playSound(){
   sound->play();
}
void Audio::stopSound(){
   sound->stop();
}
void Audio::loopSound(){
   sound->setLoop(true);
}