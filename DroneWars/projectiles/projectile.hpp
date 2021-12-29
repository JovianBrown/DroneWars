//
//  projectile.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef projectile_hpp
#define projectile_hpp

#include <stdio.h>
#include "object.hpp"
class Projectile: public Object
{
public:
    void init(int projectileType, SDL_Renderer* renderer);
    void update();
    void setActive(bool b)
    {
        this->active = b;
    }
    bool isActive()
    {
        return active;
    }
    int getType()
    {
        return type;
    }
    const int getDamage() const
    {
        return damage;
    }
    const std::string getName() const
    {
        return name;
    }
    
private:
    int projectileType;
    int type;
    int speed;
    int damage;
    std::string name;
    bool active;
};

#endif /* projectile_hpp */
