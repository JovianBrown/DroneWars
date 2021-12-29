//
//  barteritem.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/27.
//  Copyright © 2021 Jovian. All rights reserved.
//
// this class will consist of the items that will be available for purchase such as hull modifications
// blaster and other modifications

#ifndef barteritem_hpp
#define barteritem_hpp

#include <stdio.h>
#include "object.hpp"
#include "player.hpp"
enum BarterItemTypes
{
    SMALL_BLUE_BULLET,BLASTER_BLUE,BLASTER_WIDE_GREEN

};

class BarterItem : public Object
{
    public:
        int getBarterItemType();
        void init(SDL_Renderer* renderer,int barterItemType);
        const std::string getBarterItemName();
        void buyItem(Player* player);
        void setSelected(bool b)
        {
            selected = b;
        }
        bool getSelected()
        {
            return selected;
        }
        int getCost();
    
    private:
    int cost;  //cost to the player in credits
    int barterItemType;
    std::string barterItemName;
    bool selected; /// for modify state to tell if the item is currently selected

};

#endif /* barteritem_hpp */
