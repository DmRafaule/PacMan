#include "pack_E.hpp"
		  

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(800,600),"PacMan",sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(120);
    window->setPosition(sf::Vector2i(sf::VideoMode().getDesktopMode().width/2 - window->getSize().x/2,
                                     sf::VideoMode().getDesktopMode().height/2 - window->getSize().y/2));
    window->requestFocus();
    event = new sf::Event;
    
    isGUI = true;
    whichGUI[3] = true;
    gui = new GUI(whichGUI);//REMAIN ONLY THIS
}
Game::~Game(){
    if (isStartGame){
        if (isGUI) delete gui;//If player forgot to close a menu, just free
        if (isEndGame == TypeOfEnd::NOT_END){
            delete pack;
            delete world;
        }
    }
    else{//if player make decision exit now
        delete gui;
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
        
        //Menu GUI
        if (event->type == sf::Event::KeyPressed && !isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){//Push up menu if it's alredy up and it's not end game
            if (event->key.code == sf::Keyboard::Escape){//For open GUI
                isGUI=true;
                whichGUI[0] = true;
                gui = new GUI(whichGUI);
            }
        }
        else if (event->type == sf::Event::KeyPressed && isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){//Pop up menu if it's alredy push up and it's not end game
            if (event->key.code == sf::Keyboard::Escape){//for close GUI
                isGUI=false;
                whichGUI[0] = false;
                delete gui;
            }//if in this moment push enter you will exit SOLVE
            if (event->key.code == sf::Keyboard::Up)
                gui->updateMenuArrow().setPosition(gui->updateMenuArrow().getPosition().x,
                                                   gui->getMenuArrow().getGlobalBounds().top + gui->getMenuArrow().getGlobalBounds().height/5);
            if (event->key.code == sf::Keyboard::Down)
                gui->updateMenuArrow().setPosition(gui->updateMenuArrow().getPosition().x,
                                                    gui->getMenuArrow().getGlobalBounds().top + gui->getMenuArrow().getGlobalBounds().height/1.75);
            if (event->key.code == sf::Keyboard::Left)
                gui->updateMenuArrow().setPosition(gui->getMenuArrow().getGlobalBounds().left + gui->getMenuArrow().getGlobalBounds().width/7,
                                                   gui->updateMenuArrow().getPosition().y);
            if (event->key.code == sf::Keyboard::Right)
                gui->updateMenuArrow().setPosition(gui->getMenuArrow().getGlobalBounds().left + gui->getMenuArrow().getGlobalBounds().width/1.5,
                                                   gui->updateMenuArrow().getPosition().y);
        }
        
        //Begin game
        if (event->type == sf::Event::KeyPressed && isGUI && !isStartGame){//Start play in game
            if (event->key.code == sf::Keyboard::Enter){
                world = new World(window->getSize().x,window->getSize().y);
                pack = new Hero_pack();
                isGUI = false;
                whichGUI[3] = false;
                isStartGame = true;
                delete gui;
            }
        }
        else if (event->type == sf::Event::KeyPressed && isGUI && isStartGame){//Back to main menu
            if (event->key.code == sf::Keyboard::Enter){
                delete gui;
                for (bool &i : whichGUI)
                    i=false;
                whichGUI[3]=true;
                isStartGame = false;
                isEndGame = TypeOfEnd::NOT_END;
                callOnce = true;
                gui = new GUI(whichGUI);
            }
        }
    }
    if (isStartGame){
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
    else{
        gui->_update(isGUI,*window);
    }
}
void Game::render(){
    window->clear();
    
    if (isStartGame){ 
        if (isEndGame == TypeOfEnd::NOT_END){//Render only then it's not end game
            world->_render(*window);
            pack->_render(window);
        }
        gui->_render(*window,isGUI);
    }
    else{
       gui->_render(*window,isGUI);
    }
    window->display();
}