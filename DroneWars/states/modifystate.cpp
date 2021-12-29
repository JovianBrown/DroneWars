//
//  modifystate.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//
/// This is for buying / selling modifying your drone
#include "modifystate.hpp"
#include "dockstate.hpp"
#include <sstream>
ModifyState ModifyState::m_ModifyState;

void ModifyState::init(SDL_Renderer* renderer)
{
    
    printf("ModifyState Init Successful\n");
    int windowWidth = 1280;
    int windowHeight = 800;
    modifyRenderer=renderer;
    hud.initHud(modifyRenderer, windowWidth, windowHeight);
    menuGUI.initMenuGUI(modifyRenderer,windowWidth,windowHeight);
    initPlayer();
    barterSpace.x = windowWidth*.15;
    barterSpace.y = windowHeight*.10;
    barterSpace.w = windowWidth*.65;
    barterSpace.h = windowHeight*.85;
    mousePointer.w = 10;
    mousePointer.h = 10;
    selectionbox.setImage("res/selectionbox.png", modifyRenderer);
    selectionbox.setSource(0, 0, 200, 200  );
    if(player->getRareElements()>0)
    {
        rareElement.init(modifyRenderer,RARE_ELEMENT);
        items.push_back(rareElement);
    }
    if(player->getPreciousMetals()>0)
    {
        preciousMetal.init(modifyRenderer,PRECIOUS_METAL);
        items.push_back(preciousMetal);

    }
    
    blasterBlue.init(modifyRenderer, BLASTER_BLUE);
    blasterWideGreen.init(modifyRenderer,BLASTER_WIDE_GREEN);
    barterItems.push_back(blasterBlue);
    barterItems.push_back(blasterWideGreen);

}
void ModifyState::clean()
{
    printf("ModifyState Clean Successful\n");
    SDL_DestroyTexture(hud.getTexture());
    SDL_DestroyTexture(selectionbox.getTexture());
    for(Item &i : items)
    {
        SDL_DestroyTexture(i.getTexture());
    }
    items.clear();
    for(BarterItem &bi : barterItems)
    {
        SDL_DestroyTexture(bi.getTexture());
    }
    barterItems.clear();
}

void ModifyState::resume()
{
    
}

void ModifyState::pause()
{
    std::cout<<"Paused state"<<std::endl;
}
bool ModifyState::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = rectA.x;
    rightA = rectA.x + rectA.w;
    topA = rectA.y;
    bottomA = rectA.y + rectA.h;
    
    //Calculate the sides of rect B
    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = rectB.y + rectB.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
void ModifyState::handleEvents(Game *game)
{
    SDL_Event event;
    
    if (SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
            {
                case SDLK_q:
                    {
                        game->changeState(DockState::instance());
                        Savegame sg(player);
                    }
                    break;
                case SDLK_t:
                    {
                        if(playersCredits>=10)
                        {
                            player->setCredits(player->getCredits()-10);
                            player->setHps(player->getMaxHps());
                            player->setShield(player->getMaxShield());
                            Savegame sg(player);
                            initPlayer();
                        }
                        else
                        {
                            std::cout<<"Not enough credits! Try selling precious materials"<<std::endl;
                        }
                    }
                    break;
                    case SDLK_s:
                    {
                        for(Item &i: items)
                        {
                            if(i.getSelected())
                            {
                                
                                i.sellItem(player);
                                Savegame sg(player);
                                
                                initPlayer();
                            }
                        }
                        
                    
                    }
                    break;
                    case SDLK_b:
                    {
                        for(BarterItem &bi: barterItems)
                        {
                            if(bi.getSelected())
                            {
                                
                                bi.buyItem(player);
                                Savegame sg(player);
                                
                                initPlayer();
                            }
                        }
                    }
      
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                mousePointer.x = mouseX;
                mousePointer.y = mouseY;
                for(Item &i : items) //players inventory items
                {
                    if(checkCollision(mousePointer, i.getDestination()))
                    {
                        i.setSelected(true);
                        selectionbox.setDestination(i.getDestination().x, i.getDestination().y, i.getDestination().w, i.getDestination().h);
                    }
                    else
                    {
                        i.setSelected(false);
                    }
                }
                for(BarterItem &bi : barterItems) //players inventory items
                {
                    if(checkCollision(mousePointer, bi.getDestination()))
                    {
                        bi.setSelected(true);
                        selectionbox.setDestination(bi.getDestination().x, bi.getDestination().y, bi.getDestination().w, bi.getDestination().h);
                    }
                    else
                    {
                        bi.setSelected(false);
                    }
                }
            }
            break;
        }
    }
}

void ModifyState::update(Game* game)
{
}
void ModifyState::initPlayer()
{
    //// below looks complicated because we need to convert ints and floats to strings before displaying on hud
    // also need to extract the info from loadgame and load it into the player object
    /// probably fix this in the future so it doesnt use loadgame but rather passes the player pointer from Dockstate
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
    player->setCurrentWeapon(stoi(playerStats[10]));
    currentWeapon = stoi(playerStats[10]);
    
    playersWeapon.init(currentWeapon, modifyRenderer);
}

void ModifyState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(modifyRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}

void ModifyState::drawSellSpace()
{
    /////////////////// Below is a horrible way to implement the bartering area need to not use arbitrary values

    int xDest = barterSpace.x+10;
    int yDest = barterSpace.y+10;
    int tileWidth = 100;
    int tileHeight = 100;
    int itemNameX = xDest+20; ///locationX for item name text in drawText function
    int itemNameY = yDest+tileHeight;
    int itemValueX = xDest+20;// items worth in Credits X coordinate
    int itemValueY = yDest+tileHeight+15;
    menuGUI.drawText(modifyRenderer, "Item:", xDest-40,yDest+tileHeight, 255, 255, 255);
    menuGUI.drawText(modifyRenderer, "Value:", xDest-40,yDest+tileHeight+15, 255, 255, 255);
    for(int i = 0; i<items.size();i++)
    {
        items[i].setDestination(xDest,yDest, tileWidth, tileHeight);
        menuGUI.drawText(modifyRenderer, items[i].getName().c_str(), itemNameX,itemNameY, 255, 255, 255);
        menuGUI.drawText(modifyRenderer, std::to_string(items[i].getValue()).c_str(), itemValueX,itemValueY, 255, 255, 255);
        
        
        xDest+=tileWidth;
        itemNameX = xDest+20;
        itemNameY = yDest+tileHeight;
        itemValueX = xDest+20;
        itemValueY = yDest+tileHeight+15;
        
    }
    
}
void ModifyState::drawBuySpace()
{
    int xDest = barterSpace.x+10;
    int yDest = barterSpace.y+(barterSpace.h/2)+10;
    int tileWidth = 100;
    int tileHeight = 100;
    int itemNameX = xDest+20; ///locationX for item name text in drawText function
    int itemNameY = yDest+tileHeight;
    int itemValueX = xDest+20;// items worth in Credits X coordinate
    int itemValueY = yDest+tileHeight+15;
    menuGUI.drawText(modifyRenderer, "Item:", xDest-40,yDest+tileHeight, 255, 255, 255);
    menuGUI.drawText(modifyRenderer, "Cost:", xDest-40,yDest+tileHeight+15, 255, 255, 255);
    for(int i = 0; i<barterItems.size();i++)
    {
        barterItems[i].setDestination(xDest,yDest, tileWidth, tileHeight);
        
        
        menuGUI.drawText(modifyRenderer, barterItems[i].getBarterItemName().c_str(), itemNameX,itemNameY, 255, 255, 255);
        menuGUI.drawText(modifyRenderer, std::to_string(barterItems[i].getCost()).c_str(), itemValueX,itemValueY, 255, 255, 255);
        
        
        xDest+=tileWidth;
        itemNameX = xDest+20;
        itemNameY = yDest+tileHeight;
        itemValueX = xDest+20;
        itemValueY = yDest+tileHeight+15;
        
    }
}
void ModifyState::render(Game* game)
{
    SDL_RenderClear(modifyRenderer);

    SDL_SetRenderDrawColor(modifyRenderer, 0, 0, 0, 255);
    
    SDL_RenderClear(modifyRenderer);
    draw(menuGUI,0);
    draw(hud,0);
    ///////
    

    drawSellSpace();
    drawBuySpace();
    
    ///////////////////
    // Draw items for selling ////
    for(Item &i : items)
    {
        draw(i,0);
    }
    ////////////////////////////
    //// Draw items for purchase
    for(BarterItem &bi : barterItems)
    {
        draw(bi,0);
    }
    //////////////
    draw(selectionbox,0);
    ////// HUD Menu Text ///////
   
    hud.drawText(modifyRenderer, "Hull integrity (%): ", hud.getDestination().x+25, hud.getDestination().y+10, 255, 255, 255);
    
    float hullIntegrity = ((float)player->getHps()/(float)player->getMaxHps()) * 100;
    hud.drawText(modifyRenderer, std::to_string(hullIntegrity).c_str(), hud.getDestination().x+160, hud.getDestination().y+10, 255, 255, 255);
    hud.drawText(modifyRenderer, "Rare elements (kg): ", hud.getDestination().x+25, hud.getDestination().y+25, 255, 255, 255);
    hud.drawText(modifyRenderer, rareElements, hud.getDestination().x+160, hud.getDestination().y+25, 255, 255, 255);
    hud.drawText(modifyRenderer, "Metal Alloy (kg): ", hud.getDestination().x+25, hud.getDestination().y+40, 255, 255, 255);
    hud.drawText(modifyRenderer, preciousMetals, hud.getDestination().x+160, hud.getDestination().y+40, 255, 255, 255);
    hud.drawText(modifyRenderer, "Current Level: ", hud.getDestination().x+25, hud.getDestination().y+55, 255, 255, 255);
    hud.drawText(modifyRenderer, playersCurrentLevel, hud.getDestination().x+160, hud.getDestination().y+55, 255, 255, 255);
    hud.drawText(modifyRenderer, "Score: ", hud.getDestination().x+25, hud.getDestination().y+70, 255, 255, 255);
    hud.drawText(modifyRenderer, std::to_string(playersScore).c_str(), hud.getDestination().x+160, hud.getDestination().y+70, 255, 255, 255);
    hud.drawText(modifyRenderer, "Credits: ", hud.getDestination().x+25, hud.getDestination().y+85, 255, 255, 255);
    hud.drawText(modifyRenderer, std::to_string(playersCredits).c_str(), hud.getDestination().x+160, hud.getDestination().y+85, 255, 255, 255);
    hud.drawText(modifyRenderer, "Current Weapon: ", hud.getDestination().x+25, hud.getDestination().y+100, 255, 255, 255);
    hud.drawText(modifyRenderer, playersWeapon.getName().c_str(), hud.getDestination().x+160, hud.getDestination().y+100, 255, 255, 255);
  //  hud.drawText(modifyRenderer, std::to_string(currentWeapon).c_str(), hud.getDestination().x+160, hud.getDestination().y+100, 255, 255, 255);
    /////////////// Hud Menu draw Text END //////////////////////////
    ///// Menu Options GUI  END ////////

    menuGUI.drawText(modifyRenderer, "P to Purchase selected item", menuGUI.getDestination().x+20,menuGUI.getDestination().y+10, 255, 255, 255);
    menuGUI.drawText(modifyRenderer, "S to sell precious materials item ", menuGUI.getDestination().x+20, menuGUI.getDestination().y+25, 255, 255, 255);
    menuGUI.drawText(modifyRenderer, "T to refill shields and fix Hull damage ", menuGUI.getDestination().x+20, menuGUI.getDestination().y+40, 255, 255, 255);
    
    menuGUI.drawText(modifyRenderer, "Press Q to go back to main menu ", menuGUI.getDestination().x+20, menuGUI.getDestination().y+55, 255, 255, 255);
    
 
    
    SDL_RenderPresent(modifyRenderer);
}
