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
    gui = new GUI(whichGUI);
}
Game::~Game(){
    if (isStartGame){//If in game session player make desition to quit free memmory
        if (isGUI) delete gui;//If player forgot to close a menu, just free
        if (isEndGame == TypeOfEnd::NOT_END){//If player make desition exit immediately
            delete pack;
            delete world;
        }
    }
    else{//if player make decision exit from Main menu
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
        //Open menu if it's closed and you do not reach end game
        if (event->type == sf::Event::KeyPressed && !isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){
            if (event->key.code == sf::Keyboard::Escape){//For open GUI
                isGUI=true;
                whichGUI[0] = true;
                gui = new GUI(whichGUI);
            }
        }
        //Close menu if it's open and you do not reach end game and moving arrows
        else if (event->type == sf::Event::KeyPressed && isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){
            if (event->key.code == sf::Keyboard::Escape){//for close GUI
                isGUI=false;
                whichGUI[0] = false;
                delete gui;
            }
            if (event->key.code == sf::Keyboard::Up){//For moveing arrow up
                gui->updateMenuArrow().setPosition(gui->updateMenuArrow().getPosition().x,
                                                   gui->getMenuArrow().getGlobalBounds().top + gui->getMenuArrow().getGlobalBounds().height/5);
            }
            if (event->key.code == sf::Keyboard::Down){//For moveing arrow down
                gui->updateMenuArrow().setPosition(gui->updateMenuArrow().getPosition().x,
                                                    gui->getMenuArrow().getGlobalBounds().top + gui->getMenuArrow().getGlobalBounds().height/1.75);
            }
            if (event->key.code == sf::Keyboard::Left){//For moveing arrow left
                gui->updateMenuArrow().setPosition(gui->getMenuArrow().getGlobalBounds().left + gui->getMenuArrow().getGlobalBounds().width/7,
                                                   gui->updateMenuArrow().getPosition().y);
            }
            if (event->key.code == sf::Keyboard::Right){//For moveing arrow right
                gui->updateMenuArrow().setPosition(gui->getMenuArrow().getGlobalBounds().left + gui->getMenuArrow().getGlobalBounds().width/1.5,
                                                   gui->updateMenuArrow().getPosition().y);
            }
        }

        //Interact with menu, before start actual game, after end of game(all kind of endings)
        if (event->type == sf::Event::KeyPressed && isGUI && !isStartGame){//For interact with game before start actual game
            if (event->key.code == sf::Keyboard::Enter){
                if (gui->updateMenuArrow().getPosition().y <= 230 ){//Starting game
                    world = new World(window->getSize().x,window->getSize().y);
                    pack = new Hero_pack();
                    isGUI = false;
                    whichGUI[3] = false;
                    isStartGame = true;
                    delete gui;
                }
                if (gui->updateMenuArrow().getPosition().y <= 330 && gui->updateMenuArrow().getPosition().y > 230 ){//Open window with settings
                    printf("settings\n");
                }
                if (gui->updateMenuArrow().getPosition().y > 330 ){//Quit from the game
                    window->close();
                }
            }
            if (event->key.code == sf::Keyboard::Up && gui->updateMenuArrow().getPosition().y >= 200){//For moving arrow up
                gui->updateMenuArrow().move(0,-120);
            }
            if (event->key.code == sf::Keyboard::Down && gui->updateMenuArrow().getPosition().y <= 330){//For moving arrow down
                gui->updateMenuArrow().move(0,120);
            }
        }
        else if (event->type == sf::Event::KeyPressed && isGUI && isStartGame){//For interact with menu and interact with game on stage game over
            if (event->key.code == sf::Keyboard::Enter && !whichGUI[0]){//For exit to main menu after game over(any type)
                delete gui;
                for (bool &i : whichGUI)
                    i=false;
                whichGUI[3]=true;
                isStartGame = false;
                isEndGame = TypeOfEnd::NOT_END;
                callOnce = true;
                gui = new GUI(whichGUI);
            }
            if (event->key.code == sf::Keyboard::Enter && whichGUI[0]){//for interact with menu 
                //this is menu
                if (static_cast<int>(gui->updateMenuArrow().getPosition().x) == 185 && static_cast<int>(gui->updateMenuArrow().getPosition().y) == 240){
                    delete gui;
                    for (bool &i : whichGUI)
                        i=false;
                    whichGUI[3]=true;
                    isStartGame = false;
                    isEndGame = TypeOfEnd::NOT_END;
                    callOnce = true;
                    gui = new GUI(whichGUI); 
                }                    
                //this is settings
                if (static_cast<int>(gui->updateMenuArrow().getPosition().x) == 185 && static_cast<int>(gui->updateMenuArrow().getPosition().y) == 314){

                }
                //this is help
                if (static_cast<int>(gui->updateMenuArrow().getPosition().x) == 500 && static_cast<int>(gui->updateMenuArrow().getPosition().y) == 240){

                }
                //this is quit
                if (static_cast<int>(gui->updateMenuArrow().getPosition().x) == 500 && static_cast<int>(gui->updateMenuArrow().getPosition().y) == 314){
                    window->close();     
                }                
                //Why I use this magic number? because I want not make another uniqe f-tion only for this part of code ... so
            }
        }
    }
    if (isStartGame){
        if (!isGUI){//If esc is pressed game menu open (also make some pausa)
            if (isEndGame == TypeOfEnd::NOT_END){//For updating game till it's not end game
                pack->_update(*event, *window, world->_getTiles(),world->_getGhost(),globalTime,isEndGame);
                world->_update(*window,world->_getTiles(),pack->_getPack());
            }
            if (isEndGame == TypeOfEnd::BAD_END && callOnce){//Call only once when game end(bad end)(free memory and display new "window")
                isGUI=true;
                whichGUI[1] = true;
                delete pack;
                delete world;
                callOnce = false;
                gui = new GUI(whichGUI);
            }
            if (isEndGame == TypeOfEnd::GOOD_END && callOnce){//As  bad end but whith  other displaying "window" and text
                isGUI=true;
                whichGUI[2] = true;
                delete pack;
                delete world;
                callOnce = false;
                gui = new GUI(whichGUI);
            }
            //MORE ENDINGS IN THE FUTURE
        }
        gui->_update(isGUI,*window);
    }
    else{//For update start menu
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
    else{//For render start menu
       gui->_render(*window,isGUI);
    }
    
    window->display();
}