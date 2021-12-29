//
//  barteritem.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/27.
//  Copyright © 2021 Jovian. All rights reserved.
//
#include "barteritem.hpp"
#include "savegame.hpp"

void BarterItem::init(SDL_Renderer *renderer, int barterItemType)
{

   if(barterItemType ==  BLASTER_BLUE)
   {
       this->setSource(0, 0, 100, 100);

       this->barterItemType = barterItemType;
       this->setImage("res/bluelaserwide.png", renderer);
       this->cost = 50;
       this->barterItemName = "Blue Blaster";
   }
    if(barterItemType ==  BLASTER_WIDE_GREEN)
    {
        this->setSource(0, 0, 200, 100);

        this->setImage("res/greenlaserwide.png", renderer);
        this->cost = 100;
        this->barterItemType = barterItemType;
        this->barterItemName = "Green Blaster";

        
    }
    
}
void BarterItem::buyItem(Player* player)
{
    if(barterItemType ==  BLASTER_BLUE && player->getCredits()>= this->getCost())
    {
        player->setCurrentWeapon(BLASTER_BLUE);
        player->setCredits(player->getCredits()-this->getCost());
        Savegame sg(player);
    }
    if(barterItemType ==  BLASTER_WIDE_GREEN && player->getCredits()>= this->getCost())
    {
        player->setCurrentWeapon(BLASTER_WIDE_GREEN);
        player->setCredits(player->getCredits()-this->getCost());
        Savegame sg(player);

    }
    
 
    
}
const std::string BarterItem::getBarterItemName()
{
    return barterItemName;
}

int BarterItem::getCost()
{
    return cost;
}
int BarterItem::getBarterItemType()
{
    return barterItemType;
}

