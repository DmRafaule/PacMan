#include "pack_E.hpp"
		  

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(800,600),"PacMan",sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(120);
    window->setPosition(sf::Vector2i(sf::VideoMode().getDesktopMode().width/2 - window->getSize().x/2,
                                     sf::VideoMode().getDesktopMode().height/2 - window->getSize().y/2));
    window->requestFocus();
    event = new sf::Event;
    
    isGUI       = true;//First window 4 ghost will display on start
    whichGUI[3] = true;//Main menu also will display on start
    gui         = new GUI(whichGUI);
    audio       = new Audio(1);//Openning will play
    audio->loadSound("../audio/opening.wav");
    audio->playSound();
}
Game::~Game(){
    if (isStartGame){                           //If in game session player make desition to 'quit' free memmory
        if (isGUI) delete gui;                  //If player forgot to close a menu, just free
        if (isEndGame == TypeOfEnd::NOT_END){   //If player make desition exit immediately in game session 'don't push quit'
            delete pack;
            delete world;
        }
    }
    else delete gui;                            //if player make decision exit from Main menu
        
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
        
        /*Menu in game session*/
        //Open menu if it's closed and you do not reach end game
        if (event->type == sf::Event::KeyPressed && !isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){
            if (event->key.code == sf::Keyboard::Escape){//For open GUI
                audio->loadSound("../audio/switch.wav");
                isGUI           = true;                 //Now some interface opened
                whichGUI[0]     = true;                 //Now menu in game session opened
                whichGUI[4]     = false;                //Now start menu is closed
                gui             = new GUI(whichGUI);    //Create window for menu in game session
            }
        }
        //Close menu if it's open and you do not reach end game and moving arrows
        else if (event->type == sf::Event::KeyPressed && isGUI && isEndGame == TypeOfEnd::NOT_END && isStartGame){
            /*In menu in game session*/    
            if (event->key.code == sf::Keyboard::Escape){//for close GUI
                audio->loadSound("../audio/opening.wav");
                isGUI           = false;            //Now any interfaces are closed
                whichGUI[0]     = false;            //Now menu in game session closed
                delete gui;                         //Free memmory
            }
            if (event->key.code == sf::Keyboard::Up && !whichGUI[4]){       //For moveing arrow up
                audio->loopSound(false);
                audio->playSound();
                gui->getArrow().setPosition(gui->getArrow().getPosition().x,
                                                   gui->getMenu().getGlobalBounds().top + gui->getMenu().getGlobalBounds().height/5);
            }
            if (event->key.code == sf::Keyboard::Down && !whichGUI[4]){     //For moveing arrow down
                audio->loopSound(false);
                audio->playSound();
                gui->getArrow().setPosition(gui->getArrow().getPosition().x,
                                                   gui->getMenu().getGlobalBounds().top + gui->getMenu().getGlobalBounds().height/1.75);
            }
            if (event->key.code == sf::Keyboard::Left && !whichGUI[4]){     //For moveing arrow left
                audio->loopSound(false);
                audio->playSound();
                gui->getArrow().setPosition(gui->getMenu().getGlobalBounds().left + gui->getMenu().getGlobalBounds().width/7,
                                                   gui->getArrow().getPosition().y);
            }
            if (event->key.code == sf::Keyboard::Right && !whichGUI[4]){    //For moveing arrow right
                audio->loopSound(false);
                audio->playSound();
                gui->getArrow().setPosition(gui->getMenu().getGlobalBounds().left + gui->getMenu().getGlobalBounds().width/1.5,
                                                   gui->getArrow().getPosition().y);
            }
        }



        /*Start menu,*/
        if (event->type == sf::Event::KeyPressed && isGUI && !isStartGame){             //For interact with game before start actual game
            if (event->key.code == sf::Keyboard::Enter){                                //For activate item in start menu
                //Starting game
                if (gui->getArrow().getPosition().y <= 230 ){
                    if (!whichGUI[5]){
                        audio->stopSound();
                        world           = new World(window->getSize().x, window->getSize().y, optionMap);//Create world
                        pack            = new Hero_pack();  //Create pack
                        isGUI           = false;            //Now any interfaces are closed         
                        whichGUI[3]     = false;            //Now starting menu are closed
                        whichGUI[5]     = false;            //Now settings also closed
                        isStartGame     = true;             //Game has start
                        delete gui;                         //Delete gui
                    }
                }
                //Open window with settings
                if (gui->getArrow().getPosition().y <= 330 && gui->getArrow().getPosition().y > 230 ){
                    if (!whichGUI[5]){
                        delete gui;                     //Cleare before start
                        for (auto &i : whichGUI)
                            i = false;
                        whichGUI[3] = true;             //Now starting menu are open
                        whichGUI[5] = true;             //Now settings are open
                        gui         = new GUI(whichGUI);//Create settings window
                    }
                }
                //Quit from the game
                if (gui->getArrow().getPosition().y > 330 ){
                    if (whichGUI[5]){//exit In settings 
                        delete gui;
                        for (auto &i : whichGUI)
                            i = false;
                        whichGUI[3] = true;    
                        gui = new GUI(whichGUI);
                    }
                    else//Exit In main menu
                        window->close();
                }
            }
            //For moving arrow up
            if (event->key.code == sf::Keyboard::Up && gui->getArrow().getPosition().y >= 200){
                gui->getArrow().move(0,-120);
            }
            //For moving arrow down
            if (event->key.code == sf::Keyboard::Down && gui->getArrow().getPosition().y <= 330){
                gui->getArrow().move(0,120);
            }
            if (whichGUI[5]){//Keys left, right(in sub menu settings)
                //Keys for maps
                if (gui->getArrow().getPosition().y <= 230){
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
                //For volume
                if (gui->getArrow().getPosition().y <= 330 && gui->getArrow().getPosition().y > 230 ){
                    if (event->key.code == sf::Keyboard::Right){//Increase volume
                        optionVolume++;
                        gui->getVolume(&optionVolume);
                        delete audio;
                        audio = new Audio(optionVolume);
                        audio->loadSound("../audio/opening.wav");
                        audio->playSound();
                        audio->loopSound(true);
                    }
                    if (event->key.code == sf::Keyboard::Left){//Shrink volume
                        if (optionVolume>=1)
                            optionVolume--;   
                        gui->getVolume(&optionVolume);
                        delete audio;
                        audio = new Audio(optionVolume);
                        audio->loadSound("../audio/opening.wav");
                        audio->playSound();
                        audio->loopSound(true);
                    }
                }
            }
        }
        /*Pseudo menu in games ending,and active menu items in menu session*/
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
                //this is menu(back to start menu)
                if (static_cast<int>(gui->getArrow().getPosition().x) == 185 && static_cast<int>(gui->getArrow().getPosition().y) == 240){
                    audio->loadSound("../audio/opening.wav");
                    audio->playSound();
                    //Clean up 
                    delete pack;
                    delete world;
                    delete gui;
                    for (bool &i : whichGUI)
                         i = false;
                    whichGUI[3]     = true;                 //Now window is start menu
                    isStartGame     = false;                //Now we don't play in actual game 
                    isEndGame       = TypeOfEnd::NOT_END;   //We exit from game session not in the end
                    callOnce        = true;                 //For free mem only once
                    gui             = new GUI(whichGUI);    //Create window for start menu
                }                    
                //this is settings
                if (static_cast<int>(gui->getArrow().getPosition().x) == 185 && static_cast<int>(gui->getArrow().getPosition().y) == 314){
                    //In the future
                }
                //this is help
                if (static_cast<int>(gui->getArrow().getPosition().x) == 500 && static_cast<int>(gui->getArrow().getPosition().y) == 240){
                    delete gui;                 //Free mem
                    for (bool &i : whichGUI)    //Any kind of GUI not show
                        i=false;
                    whichGUI[4] = true;         //Now display little help
                    gui         = new GUI(whichGUI);
                }
                //this is quit
                if (!whichGUI[4]){//So this is my 8 or more hours of finding THIS F***ING segfault. Just use gdb, realy tool of gods(1 min and segfaule disappear)
                    if (static_cast<int>(gui->getArrow().getPosition().x) == 500 && static_cast<int>(gui->getArrow().getPosition().y) == 314){
                        window->close();     
                    }
                }                
                //Why I use this magic number? because I want not make another uniqe f-tion only for this part of code ... so
            }
        }
    }
    //For update actual game
    if (isStartGame){
        if (!isGUI){//If esc are pressed game menu open (also make pausa)
            if (isEndGame == TypeOfEnd::NOT_END){//For updating game till it's not end game
                pack->_update(*event, *window, world->_getTiles(),world->_getGhost(),globalTime,isEndGame);
                world->_update(*window,world->_getTiles(),pack->_getPack());
            }
            if (isEndGame == TypeOfEnd::BAD_END && callOnce){//Call only once when game end(bad end)(free memory and display new "window")
                audio->playSound();
                isGUI           = true;                 //Display window with ending
                for (auto& i: whichGUI)
                    i = false;
                whichGUI[1]     = true;                 //Display window with ending
                delete pack;                            //Free mem
                delete world;
                callOnce        = false;                //free mem only onse for session
                gui             = new GUI(whichGUI);    
            }
            if (isEndGame == TypeOfEnd::GOOD_END && callOnce){//As  bad end but whith  other displaying "window" and text
                audio->playSound();
                isGUI           = true;                 //Display window with ending
                for (auto& i: whichGUI)
                    i = false;
                whichGUI[2]     = true;                 //Display window with ending
                delete pack;                            //Free mem
                delete world;
                callOnce        = false;                //free mem only onse for session
                gui             = new GUI(whichGUI);
            }
            //MORE ENDINGS IN THE FUTURE
        }
        gui->_update(isGUI,*window);
    }
    //For update start menu
    else{ 
        gui->_update(isGUI,*window);
    }
}
void Game::render(){
    window->clear();
    //For render actual game
    if (isStartGame){ 
        if (isEndGame == TypeOfEnd::NOT_END){//Render only then if it's not end game
            world->_render(*window);
            pack->_render(window);
        }
        gui->_render(*window,isGUI);
    }
    //For render start menu
    else{
       gui->_render(*window,isGUI);
    }
    
    window->display();
}