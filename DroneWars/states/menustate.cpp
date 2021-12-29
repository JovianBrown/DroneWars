//
//  menustate.cpp
//  DroneWarsV3
//
//  Created by Jovian on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "menustate.hpp"
#include "playstate.hpp"
#include "dockstate.hpp"
#include "briefstate.hpp"
MenuState MenuState::m_MenuState;

void MenuState::init(SDL_Renderer* renderer)
{
    menuRenderer = renderer;
    splashScreen.setImage("res/splashv4.png", menuRenderer);
    if(splashScreen.getTexture()==NULL)
    {
        std::cout<<"Unable to load texture in menustate init"<<std::endl;
    }
    splashScreen.setSource(0, 0, 1920,1080 );
    splashScreen.setDestination(0, 0, 1280, 800);
    int windowWidth = 1280;
    int windowHeight = 800;
    menuGUI.initMenuGUI(renderer, windowWidth, windowHeight);
    printf("MenuState Init Successful\n");
    
}



void MenuState::pause()
{
    printf("MenuState Paused\n");
}

void MenuState::resume()
{
    printf("MenuState Resumed\n");
}
Player* MenuState::createNewPlayer()
{
    ////////////  new player stufff //////////
    
    ////  instatiate everything as the defaults ////
    player = new Player();
    player->setCurrentLevel(1);
    player->setHps(100);
    player->setMaxHps(100);
    player->setEnergy(100);
    player->setMaxEnergy(100);
    player->setShield(100);
    player->setMaxShield(100);
    player->setRareElements(0);
    player->setPreciousMetals(0);
    player->setScore(0);
    player->setCurrentWeapon(0);   ///weapon set to first basic weapon
    ///////// end new player stuff ///////
    return player;
}

void MenuState::handleEvents(Game* game) //put our exit function back in business
// we can now quit with cross in corner.
{
    SDL_Event event;
    
    if (SDL_WaitEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_n:   //new game
                    {
                        game->changeState(BriefState::instance());
                        player = createNewPlayer();
                        /// OverWrite old game ///
                        Savegame sg(player);
                        BriefState::instance()->loadMissionBriefing(player);
                    }
                    break;
                    case SDLK_l: //Load game
                        {
                            Loadgame  lg;
                            std::vector<std::string> playerStats = lg.getPlayerStats();
                            std::cout<<"player stats"<<std::endl;

                            player = new Player();
                            player->setHps(stoi(playerStats[0]));
                            player->setMaxHps(stoi(playerStats[1]));
                            player->setMaxAcc(stoi(playerStats[2]));
                            player->setMaxShield(stoi(playerStats[3]));
                            player->setRareElements(stoi(playerStats[4]));
                            player->setPreciousMetals(stoi(playerStats[5]));
                            player->setEnergy(stoi(playerStats[6]));
                            unsigned int playersLevel =stoi(playerStats[7]);
                            player->setCurrentLevel(playersLevel);
                            player->setScore(stoi(playerStats[8]));
                            player->setCredits(stoi(playerStats[9]));
                            player->setCurrentWeapon(stoi(playerStats[10]));
                            game->changeState(DockState::instance());
                            
                        }
                        break;
                    case SDLK_q:
                        game->quit();
                        break;
                        
                }

        }
    }
}

void MenuState::update(Game* game)
{
    
}
void MenuState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(menuRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}


void MenuState::render(Game* game)
{

    SDL_RenderClear(menuRenderer);
    draw(splashScreen,0);
    draw(menuGUI,0);
    menuGUI.drawText(menuRenderer, "Press N for new game", menuGUI.getDestination().x+20, menuGUI.getDestination().y+10, 255, 255, 255);
    menuGUI.drawText(menuRenderer, "Press L to load game", menuGUI.getDestination().x+20, menuGUI.getDestination().y+25, 255, 255, 255);
    
    menuGUI.drawText(menuRenderer, "Press Q to quit game", menuGUI.getDestination().x+20, menuGUI.getDestination().y+40, 255, 255, 255);

    SDL_RenderPresent(menuRenderer);
}
void MenuState::clean()
{
    printf("MenuState Clean Successfully\n");
    SDL_DestroyTexture(splashScreen.getTexture());
    menuGUI.clean();
    
}
