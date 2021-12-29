//
//  hud.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//


#include "hud.hpp"

void Hud::initHud(SDL_Renderer* renderer,int &windowWidth, int &windowHeight)
{
    setImage("res/screenv1.png", renderer);
    setSource(0, 0, 500, 175);
    setDestination(980, 0, 300, 170);
    if(this->getTexture())
    {
        std::cout<<"loaded HUD texture successfully"<<std::endl;
        
    }
    else
    {
        std::cout<<"unable to load HUD texture"<<std::endl;
    }
    initGUI(windowWidth, windowHeight);
    
}


void Hud::clean()
{
    std::cout<<"Hud cleaned successfully"<<std::endl;
    SDL_DestroyTexture(this->getTexture());
}

