//
//  menugui.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "menugui.hpp"

void MenuGUI::initMenuGUI(SDL_Renderer* renderer,int &wW, int &wH)
{

    setImage("res/screenv1.png", renderer);
    if(this->getTexture())
    {
        std::cout<<"loaded MenuGUI texture successfully"<<std::endl;
        
    }
    
    windowWidth = wW;
    windowHeight = wH;
    setSource(0, 0, 500, 175);
    setDestination(980, 300, 300, 170);

    initGUI(windowWidth, windowHeight); //initializes fonts for menuGUI
    
   
}
void MenuGUI::update()
{
    
}

void MenuGUI::clean()
{
    std::cout<<"Menu GUI cleaned successfully"<<std::endl;
    SDL_DestroyTexture(this->getTexture());
    TTF_Quit();
}

