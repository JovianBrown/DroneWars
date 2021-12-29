//
//  Entity.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <stdio.h>
#include "object.hpp"
#include <vector>
enum Directions
{
    NORTH,SOUTH,EAST,WEST
};
//implements animations , the animations are stored in a vector that keeps track of the proper frame to display
//also implements basic physics and keeps track of collisions 
class Entity : public Object
{
public:
    void update();
    void animate();
    void animateEntity();

    void resetAnimation();
    int createCycle(int totalrows, int totalcolumns,int startingrow, int startingcolumn,int w, int h,int speed, bool repeat,bool reversed, bool stopOnFinal);
    struct cycle //this defines our animation data type
    {
        int row;
        int column;
        int currentcolumn;
        int startingcolumn;
        int startingrow;
        int width;
        int height;
        int frames;
        int speed;
        int tick;
        int currentFrame;
        bool repeat;
        bool reversed;
        bool stopOnFinal;
        uint32_t id;
    };
    void setCurrentAnimation(int c )
    {
        currentAnimation = c;
    }
    int getCurrentAnimation()
    {
        return currentAnimation;
    }
  
    const bool isActive() const
    {
        return active;
    }
    void  setActive(bool b )
    {
        active=b;
    }
    ////physics//////////////
    void setXAcc(float xAcc);
    void setYAcc(float xAcc);
    void setMaxAcc(float maxAcc);
    void setMass(int m);
    void setDefaultAcc(float maxAcc);
    void checkSpeed();
    float applyForce(float force, int direction);
    float getXAcc()
    {
        return xAcc;
    }
    float getYAcc()
    {
        return yAcc;
    }
    float getMaxAcc()
    {
        return maxAcc;
    }
    const float getDefaultAcc() const
    {
        return defaultAcc;
    }
    const int getMass() const
    {
        return mass;
    }
    bool didJustCollide()
    {
        return justCollided;
    }
    void setJustCollided(bool b )
    {
        justCollided=true;
    }
    ////////// physics end /////////
    /////// Entity Stats /////
    
    const int getHps()
    {
        return hps;
    }
    void setHps(int hp)
    {
        hps=hp;
    }
    const int getMaxHps() const
    {
        return maxHps;
    }
    void setMaxHps(int maxH)
    {
        maxHps = maxH;
    }
    void setRotationAngle(int rotationAngle)
    {
        this->rotationAngle = rotationAngle;
    }
    const int getRotationAngle() const
    {
        return rotationAngle;
    }
     /////// End Entity Stats /////
    std::vector<cycle> animations;
    int currentAnimation;
 

private:
   
   
    bool justCollided;
    bool active;
    float xAcc;
    float yAcc;
    float maxAcc;
    float defaultAcc; //the entities actual acceleration
    int mass;
    int hps;
    int maxHps;
    int rotationAngle;
 
};
#endif /* entity_hpp */
