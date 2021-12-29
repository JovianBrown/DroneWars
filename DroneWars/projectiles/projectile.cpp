//
//  projectile.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "projectile.hpp"
enum PROJECTILE_TYPES
{
    SMALL_BLUE_BULLET,BLUE_LASER_WIDE,GREEN_SUPER_WIDE
};
void Projectile::init(int type,SDL_Renderer* renderer)
{
    this->projectileType = type;
    if(type == SMALL_BLUE_BULLET)
    {
        setImage("res/bluebullet.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 20, 20);
        this->speed = 18;
        this->type = SMALL_BLUE_BULLET;
        this->damage = 20;
        this->name = "Small Blaster";
    }
    if(type == BLUE_LASER_WIDE)
    {
        setImage("res/bluelaserwide.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 25, 25);
        this->speed = 14;
        this->type = BLUE_LASER_WIDE;
        this->damage = 30;
        this->name = "Wide Blue Blaster";

    }
    if(type == GREEN_SUPER_WIDE)
    {
        setImage("res/greenlaserwide.png", renderer);
        setSource(0, 0, 200, 100);
        setDestination(0, 0, 70, 35);
        this->speed = 16;
        this->type = GREEN_SUPER_WIDE;
        this->damage = 38;
        this->name = "Super Wide Blaster";
        
    }
}

void Projectile::update()
{
    
    setDestination(getDestination().x, getDestination().y-speed, getDestination().w, getDestination().h);
}
