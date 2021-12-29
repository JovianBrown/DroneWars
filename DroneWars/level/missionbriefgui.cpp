//
//  missionbriefgui.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "missionbriefgui.hpp"

void MissionBriefGUI::init(SDL_Renderer* renderer)
{
    briefRenderer = renderer;
    this->setImage("res/screenv1.png", briefRenderer);
    this->setSource(0, 0, 500, 175);
    this->setDestination(200, 200, 500, 175);
    std::cout<<"Mission Brief GUI initialized."<<std::endl;
    
}


MissionBriefGUI::~MissionBriefGUI()
{
    std::cout<<"Called MissionBriefGUI destructor"<<std::endl;
    SDL_DestroyTexture(this->getTexture());
    
}
