#include "pack_E.hpp"
		  

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(800,600),"PacMan",sf::Style::Default);
    window->setFramerateLimit(120);
    pack = new Hero_pack();
    event = new sf::Event;
    world = new World(window->getSize().x,window->getSize().y);
}
Game::~Game(){
    delete window;   
    delete event;
    delete world;
}

void Game::run(){
    while(window->isOpen()){
        update();
        render();
    }
}
void Game::update(){
    while (window->pollEvent(*event)){
        if (event->type == sf::Event::Closed)
            window->close();
            
    }
    pack->_update(*event,*window);
    world->_update();
}
void Game::render(){
    window->clear();

    world->_render(*window);
    pack->_render(window);
    
    window->display();
}