//
//  background.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "background.hpp"
void Background::update(int &levelHeight)
{

        setDestination(getDestination().x, getDestination().y+speed, getDestination().w, getDestination().h);
        if(getDestination().y>levelHeight)
        {
            setDestination(getDestination().x, 0, getDestination().w, getDestination().h);
        }
}
