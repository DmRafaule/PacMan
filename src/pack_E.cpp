#include "pack_E.hpp"
		  

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(800,600),"PacMan",sf::Style::Default);
    window->setFramerateLimit(120);
    window->setPosition(sf::Vector2i(sf::VideoMode().getDesktopMode().width/2 - window->getSize().x/2,
                                     sf::VideoMode().getDesktopMode().height/2 - window->getSize().y/2));
    window->requestFocus();

    world = new World(window->getSize().x,window->getSize().y);
    pack = new Hero_pack();
    event = new sf::Event;
}
Game::~Game(){
    delete event;
    delete pack;
    delete world;
    delete window;  
}

void Game::run(){
    while(window->isOpen()){
        update();
        render();
    }
}
void Game::update(){
    while (window->pollEvent(*event)){
        if (event->type == sf::Event::Closed){
            window->close();
        }
        if (event->type == sf::Event::KeyPressed && !isMenu){
            if (event->key.code == sf::Keyboard::G){//For open menu
                isMenu=true;
                menu = new Menu(*window);
            }
        }
        else if (event->type == sf::Event::KeyPressed && isMenu){
            if (event->key.code == sf::Keyboard::G){//for close menu
                isMenu=false;
                delete menu;
            }
        }
    }
    if (!isMenu){//pop up menu/pausa 
        pack->_update(*event, *window, world->_getTiles());
        world->_update(*window,world->_getTiles(),pack->_getPack());
    }
    menu->_update(isMenu,*window);
}
void Game::render(){
    window->clear();
    
    world->_render(*window);
    pack->_render(window);
    menu->_render(isMenu);
    
    window->display();
}