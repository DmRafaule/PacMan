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
    if (isGUI) delete gui;//If player forgot to close a menu, just free
    if (isEndGame == TypeOfEnd::NOT_END){
        delete pack;
        delete world;
    }
    delete event;
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
        if (event->type == sf::Event::KeyPressed && !isGUI && isEndGame == TypeOfEnd::NOT_END){//Push up menu if it's alredy up and it's not end game
            if (event->key.code == sf::Keyboard::Escape){//For open GUI
                isGUI=true;
                whichGUI[0] = true;
                gui = new GUI(whichGUI);
            }
        }
        else if (event->type == sf::Event::KeyPressed && isGUI && isEndGame == TypeOfEnd::NOT_END){//Pop up menu if it's alredy push up and it's not end game
            if (event->key.code == sf::Keyboard::Escape){//for close GUI
                isGUI=false;
                whichGUI[0] = false;
                delete gui;
            }
        }
    }
    if (!isGUI){//pop up GUI/pausa //HERE add menu and end to game//REMOVE CLASS menu(all gui have to be in GUI)
        if (isEndGame == TypeOfEnd::NOT_END){//Update only then it's not end gam
            pack->_update(*event, *window, world->_getTiles(),world->_getGhost(),globalTime,isEndGame);
            world->_update(*window,world->_getTiles(),pack->_getPack());
        }
        if (isEndGame == TypeOfEnd::BAD_END && callOnce){//Call only once when game end(free memory and display Some new GUI)
            isGUI=true;
            whichGUI[1] = true;
            delete pack;
            delete world;
            callOnce = false;
            gui = new GUI(whichGUI);
        }
        if (isEndGame == TypeOfEnd::GOOD_END && callOnce){
            isGUI=true;
            whichGUI[2] = true;
            delete pack;
            delete world;
            callOnce = false;
            gui = new GUI(whichGUI);
        }
    }
    gui->_update(isGUI,*window);
}
void Game::render(){
    window->clear();
    
    if (isEndGame == TypeOfEnd::NOT_END){//Render only then it's not end game
        world->_render(*window);
        pack->_render(window);
    }
    gui->_render(*window,isGUI);

    window->display();
}