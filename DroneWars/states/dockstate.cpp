
//
//  DockState.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "dockstate.hpp"
#include "loadgame.hpp"
#include "mapstate.hpp"
#include "briefstate.hpp"
DockState DockState::m_dockState;

void DockState::init(SDL_Renderer* renderer)
{
    dockRenderer= renderer;

    int windowWidth = 1280;
    int windowHeight = 800;
    levelHeight= 1280;
    levelH = &levelHeight;
    dockScreen.setImage("res/dockingbayholdout.png", dockRenderer);
    dockScreen.setSource(0, 0, 1920, 1280);
    dockScreen.setDestination(0, 0, 1280, 800);
    hud.initHud(dockRenderer, windowWidth, windowHeight);
  //  menu.initMenuGUI(dockRenderer, windowWidth, windowHeight);
    background.setImage("res/starsBG640.png", dockRenderer);
    background.setSource(0, 0, windowWidth, windowHeight);
    background.setDestination(0, 0, 1280, 1280);
    background.setSpeed(1);
    initPlayer();
    dockMenu.initMenuGUI(dockRenderer, windowWidth, windowHeight);
    
    printf("DockState Init Successful\n");
    

}

void DockState::initPlayer()
{
    Loadgame loadGame;
    
    playerStats = loadGame.getPlayerStats();
    playersCurrentLevel = playerStats[7].c_str();
    playerHps = playerStats[0].c_str();
    maxHps = playerStats[1].c_str();
    u_playerHps = atoi(playerHps);
    u_playerMaxHps = atoi(maxHps);
    hullIntegrity = ((float)u_playerHps/(float)u_playerMaxHps)*100;
    rareElements = playerStats[4].c_str();
    preciousMetals = playerStats[5].c_str();
    playersScore = stoi(playerStats[8].c_str());
    playersCredits = stoi(playerStats[9].c_str());
    playersCurrentWeapon = atoi(playerStats[10].c_str());
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
    player->setScore(playersScore);
    player->setCredits(playersCredits);
    player->setCurrentWeapon(playersCurrentWeapon);
}

void DockState::resume()
{
    
}

void DockState::pause()
{
    std::cout<<"Paused state"<<std::endl;
}

void DockState::handleEvents(Game *game)
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_p:
                        game->pushState(ModifyState::instance());
                        break;
                    case SDLK_q:
                        game->changeState(MenuState::instance());
                    break;
                    case SDLK_b:
                     //   game->pushState(BriefState::instance());
                        game->changeState(BriefState::instance());
                        BriefState::instance()->loadMissionBriefing(player);
                       // PlayState::init(game->getRenderer());
                    break;
                    case SDLK_v:    //view map
                        game->changeState(MapState::instance());
                        break;
                    case SDLK_s:    // save game
                        Savegame sg(player);
                        break;
                }
                
        }
    }
}

void DockState::update(Game* game)
{
    background.update(*levelH);
    dockMenu.update();
}
void DockState::drawBackground(Background &background)
{
    SDL_Rect destination = background.getDestination();
    SDL_Rect source = background.getSource();  //need to set this as a constant
    SDL_Rect destination2;
    destination2.h=destination.h;
    destination2.w=destination.w;
    destination2.x=destination.x;
    destination2.y=destination.y-1280;
    
    SDL_Rect source2 = background.getSource();
    SDL_RenderCopyEx(dockRenderer,background.getTexture(),&source,&destination,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(dockRenderer,background.getTexture(),&source2,&destination2,0,NULL,SDL_FLIP_NONE);
}

void DockState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(dockRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}

void DockState::render(Game* game)
{
    SDL_SetRenderDrawColor(dockRenderer, 0 , 0, 0, 255);
    SDL_RenderClear(dockRenderer);
    drawBackground(background);
    draw(dockScreen,0); //dockScreenBG
    draw(dockMenu,0);  ///MenuGui
  //  drawMenu(dockMenu); //menu text
    draw(hud,0);
    ////// HUD Menu Text ///////
    dockMenu.drawText(dockRenderer, "Press P to purchase mods and repair ship", dockMenu.getDestination().x+20, dockMenu.getDestination().y+10, 255, 255, 255);
    dockMenu.drawText(dockRenderer, "Press S to save game. ", dockMenu.getDestination().x+20, dockMenu.getDestination().y+25, 255, 255, 255);
     dockMenu.drawText(dockRenderer, "Press B to go to next mission brief", dockMenu.getDestination().x+20, dockMenu.getDestination().y+40, 255, 255, 255);
    dockMenu.drawText(dockRenderer, "Press Q to go back to main menu ", dockMenu.getDestination().x+20, dockMenu.getDestination().y+55, 255, 255, 255);
    
    hud.drawText(dockRenderer, "Hull integrity (%): ", hud.getDestination().x+25, hud.getDestination().y+10, 255, 255, 255);
    
    hud.drawText(dockRenderer, std::to_string(hullIntegrity).c_str(), hud.getDestination().x+160, hud.getDestination().y+10, 255, 255, 255);
    hud.drawText(dockRenderer, "Rare elements (kg): ", hud.getDestination().x+25, hud.getDestination().y+25, 255, 255, 255);
    hud.drawText(dockRenderer, rareElements, hud.getDestination().x+160, hud.getDestination().y+25, 255, 255, 255);
    hud.drawText(dockRenderer, "Metal Alloy (kg): ", hud.getDestination().x+25, hud.getDestination().y+40, 255, 255, 255);
    hud.drawText(dockRenderer, preciousMetals, hud.getDestination().x+160, hud.getDestination().y+40, 255, 255, 255);
    hud.drawText(dockRenderer, "Current Level: ", hud.getDestination().x+25, hud.getDestination().y+55, 255, 255, 255);
    hud.drawText(dockRenderer, playersCurrentLevel, hud.getDestination().x+160, hud.getDestination().y+55, 255, 255, 255);
    hud.drawText(dockRenderer, "Score: ", hud.getDestination().x+25, hud.getDestination().y+70, 255, 255, 255);
    hud.drawText(dockRenderer, std::to_string(playersScore).c_str(), hud.getDestination().x+160, hud.getDestination().y+70, 255, 255, 255);
    hud.drawText(dockRenderer, "Credits: ", hud.getDestination().x+25, hud.getDestination().y+85, 255, 255, 255);
    hud.drawText(dockRenderer, std::to_string(playersCredits).c_str(), hud.getDestination().x+160, hud.getDestination().y+85, 255, 255, 255);
    /////////////// Hud Menu draw Text END //////////////////////////
    SDL_RenderPresent(dockRenderer);
}

void DockState::clean()
{
    SDL_DestroyTexture(dockScreen.getTexture());
    SDL_DestroyTexture(hud.getTexture());
   // SDL_DestroyRenderer(dockRenderer);
    playerStats.clear();
    printf("DockState Clean Successful\n");
}
