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

    globalTime = globalClock.getElapsedTime();
    while (window->pollEvent(*event)){
        if (event->type == sf::Event::Closed){
            window->close();
        }
        if (event->type == sf::Event::KeyPressed && !isGUI){
            if (event->key.code == sf::Keyboard::Escape){//For open GUI
                isGUI=true;
                whichGUI[0] = true;
                gui = new GUI(whichGUI);
            }
        }
        else if (event->type == sf::Event::KeyPressed && isGUI){
            if (event->key.code == sf::Keyboard::Escape){//for close GUI
                isGUI=false;
                delete gui;
                whichGUI[0] = false;
            }
        }
    }
    if (!isGUI){//pop up GUI/pausa 
        pack->_update(*event, *window, world->_getTiles(),world->_getGhost(),globalTime);
        world->_update(*window,world->_getTiles(),pack->_getPack());
    }
    gui->_update(isGUI,*window);
}
void Game::render(){
    window->clear();
    
    world->_render(*window);
    pack->_render(window);
    gui->_render(*window,isGUI);

    window->display();
}