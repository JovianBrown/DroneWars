//
//  player.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "entity.hpp"
//Player class implements specifics for player entity. 
class Player : public Entity
{
public:
    
    //    Player(); //cant have constructor because its inheriting from object: entity
    const int getEnergy()
    {
        return energy;
    }
    const int getMaxEnergy() const
    {
        return maxEnergy;
    }
    const int getRareElements()
    {
        return rareElements;
    }
    const int getPreciousMetals()
    {
        return preciousMetals;
    }
    const int getShield()
    {
        return shield;
    }
    const int getMaxShield() const
    {
        return maxShield;
    }
    bool isReady()
    {
        return ready;
    }
    const int getLevel() const
    {
        return currentLevel;
    }
    const int getScore() const
    {
        return score;
    }
    const int getCredits() const
    {
        return credits;
    }
    const int getCurrentWeapon() const
    {
        return currentWeapon;
    }
    void setReady(bool b);
    void setEnergy(int e);
    void setMaxEnergy(int e);
    void setRareElements(int re);
    void setPreciousMetals(int p);
    void setShield(int s);
    void setMaxShield(int s);
    void setGettingReady(bool b);
    void animatePlayer();
    void setCurrentLevel(int level);
    void init(SDL_Renderer* renderer);
    void loadSaveGame();
    void setScore(int s);
    void setCredits(int c);
    void setCurrentWeapon(int w);
private:
    bool gettingReady,ready;
    int energy;
    int maxEnergy;
    int rareElements;
    int preciousMetals;
    int shield;
    int maxShield;
    int currentLevel;
    int score;
    int credits;
    int currentWeapon;
};
#endif /* player_hpp */
