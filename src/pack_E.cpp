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
    audio = new Audio(1);
    audio->loadSound("../audio/opening.wav");
    audio->playSound();
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
    delete audio;
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
                audio->loadSound("../audio/switch.wav");
                isGUI=true;
                whichGUI[0] = true;
                whichGUI[4] = false;
                gui = new GUI(whichGUI);
            }
        }
        //Close menu if it's open and you do not reach end game and moving arrows
        else if (event->type == sf::Event::KeyPressed && isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){
                
            if (event->key.code == sf::Keyboard::Escape){//for close GUI
                audio->loadSound("../audio/opening.wav");
                isGUI=false;
                whichGUI[0] = false;
                delete gui;
            }
            if (event->key.code == sf::Keyboard::Up){//For moveing arrow up
                audio->playSound();
                gui->updateMenuArrow().setPosition(gui->updateMenuArrow().getPosition().x,
                                                   gui->getMenuArrow().getGlobalBounds().top + gui->getMenuArrow().getGlobalBounds().height/5);
            }
            if (event->key.code == sf::Keyboard::Down){//For moveing arrow down
                audio->playSound();
                gui->updateMenuArrow().setPosition(gui->updateMenuArrow().getPosition().x,
                                                    gui->getMenuArrow().getGlobalBounds().top + gui->getMenuArrow().getGlobalBounds().height/1.75);
            }
            if (event->key.code == sf::Keyboard::Left){//For moveing arrow left
                audio->playSound();
                gui->updateMenuArrow().setPosition(gui->getMenuArrow().getGlobalBounds().left + gui->getMenuArrow().getGlobalBounds().width/7,
                                                   gui->updateMenuArrow().getPosition().y);
            }
            if (event->key.code == sf::Keyboard::Right){//For moveing arrow right
                audio->playSound();
                gui->updateMenuArrow().setPosition(gui->getMenuArrow().getGlobalBounds().left + gui->getMenuArrow().getGlobalBounds().width/1.5,
                                                   gui->updateMenuArrow().getPosition().y);
            }
        }

        //Interact with menu, before start actual game, after end of game(all kind of endings)
        if (event->type == sf::Event::KeyPressed && isGUI && !isStartGame){//For interact with game before start actual game
            if (event->key.code == sf::Keyboard::Enter){
                if (gui->updateMenuArrow().getPosition().y <= 230 ){//Starting game
                    if (!whichGUI[5]){
                        audio->stopSound();
                        world = new World(window->getSize().x, window->getSize().y, optionMap);
                        pack = new Hero_pack();
                        isGUI = false;
                        whichGUI[3] = false;
                        whichGUI[5] = false;
                        isStartGame = true;
                        delete gui;
                    }
                }
                if (gui->updateMenuArrow().getPosition().y <= 330 && gui->updateMenuArrow().getPosition().y > 230 ){//Open window with settings
                    if (!whichGUI[5]){
                        delete gui;
                        for (auto &i : whichGUI)
                            i = false;
                        whichGUI[3] = true;    
                        whichGUI[5] = true;
                        gui = new GUI(whichGUI);
                    }
                }
                if (gui->updateMenuArrow().getPosition().y > 330 ){//Quit from the game
                    if (whichGUI[5]){//In settings
                        delete gui;
                        for (auto &i : whichGUI)
                            i = false;
                        whichGUI[3] = true;    
                        gui = new GUI(whichGUI);
                    }
                    else//In main menu
                        window->close();
                }
            }
            if (event->key.code == sf::Keyboard::Up && gui->updateMenuArrow().getPosition().y >= 200){//For moving arrow up
                gui->updateMenuArrow().move(0,-120);
            }
            if (event->key.code == sf::Keyboard::Down && gui->updateMenuArrow().getPosition().y <= 330){//For moving arrow down
                gui->updateMenuArrow().move(0,120);
            }
            if (whichGUI[5]){//Keys lefr right
                if (gui->updateMenuArrow().getPosition().y <= 230){//Keys for maps
                    if (event->key.code == sf::Keyboard::Right){//Next map
                        if (optionMap <=2)
                            optionMap++;
                        gui->getMap(&optionMap);
                    }
                    if (event->key.code == sf::Keyboard::Left){//Previose map
                        if (optionMap >=1)
                            optionMap--;
                        gui->getMap(&optionMap);
                    }
                }
                if (gui->updateMenuArrow().getPosition().y <= 330 && gui->updateMenuArrow().getPosition().y > 230 ){//For volume
                    if (event->key.code == sf::Keyboard::Right){//Increase volume
                        optionVolume++;
                        gui->getVolume(&optionVolume);
                        delete audio;
                        audio = new Audio(optionVolume);
                        audio->loadSound("../audio/opening.wav");
                        audio->playSound();
                        audio->loopSound();
                    }
                    if (event->key.code == sf::Keyboard::Left){//Shrink volume
                        if (optionVolume>=1)
                            optionVolume--;   
                        gui->getVolume(&optionVolume);
                        delete audio;
                        audio = new Audio(optionVolume);
                        audio->loadSound("../audio/opening.wav");
                        audio->playSound();
                        audio->loopSound();
                    }
                }
            }
        }
        //For interact with menu and interact with game on stage game over
        else if (event->type == sf::Event::KeyPressed && isGUI && isStartGame){
            if (event->key.code == sf::Keyboard::Enter && !whichGUI[0] && !whichGUI[4]){//For exit to main menu after game over(any type)
                audio->playSound();
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
                    audio->loadSound("../audio/opening.wav");
                    audio->playSound();
                    delete pack;
                    delete world;
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
                    delete gui;//HERE SEGMENTATION FAULT
                    for (bool &i : whichGUI)
                        i=false;
                    whichGUI[4] = true; 
                    gui = new GUI(whichGUI);
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
                audio->playSound();
                isGUI=true;
                whichGUI[1] = true;
                delete pack;
                delete world;
                callOnce = false;
                gui = new GUI(whichGUI);
            }
            if (isEndGame == TypeOfEnd::GOOD_END && callOnce){//As  bad end but whith  other displaying "window" and text
                audio->playSound();
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