//
//  player.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "entity.hpp"
void Entity::update()
{

    this->setDestination(this->getDestination().x+this->getXAcc(), this->getDestination().y+this->getYAcc(),this->getDestination().w, this->getDestination().h);
}
void Entity::checkSpeed()
{
    if(getYAcc()>getMaxAcc())
        setYAcc(getMaxAcc());
    if(getXAcc()>getMaxAcc())
        setXAcc(getMaxAcc());
}
int Entity::createCycle(int totalrows, int totalcolumns,int startingrow,int startingcolumn,int w, int h, int speed, bool repeat, bool reversed, bool stopOnFinal)
{
    cycle tmp;
    tmp.row=totalrows;
    tmp.column=totalcolumns;
    tmp.currentcolumn=startingcolumn;
    tmp.startingrow=startingrow;
    tmp.startingcolumn=startingcolumn;
    tmp.width=w;
    tmp.height=h;
    tmp.tick=0;
    tmp.frames = totalrows*totalcolumns;
    tmp.speed=speed;
    tmp.repeat=repeat;
    tmp.reversed=reversed;
    tmp.stopOnFinal = stopOnFinal;  //stop animation on final frame
    tmp.currentFrame=0;
    if(reversed)
    {
        tmp.currentFrame=tmp.frames-1;
        tmp.tick=tmp.row-1;
        tmp.currentcolumn=tmp.column-1;
    }
    animations.push_back(tmp);
    tmp.id=(uint32_t)animations.size()-1;
    std::cout<<"animation id"<<(uint32_t)animations.size()-1<<std::endl;
    return (uint32_t)animations.size()-1;
}
float Entity::applyForce(float force, int direction)
{
    float accelleration = force/getMass();
    if(direction==NORTH)
    {
        setYAcc(getYAcc()-accelleration);
    }
    if(direction==SOUTH)
    {
        setYAcc(getYAcc()+accelleration);
    }
    if(direction==WEST)
    {
        setXAcc(getXAcc()-accelleration);
    }
    if(direction==EAST)
    {
        setXAcc(getXAcc()+accelleration);
    }
    return accelleration;
}
void Entity::resetAnimation()
{
    std::cout<<"called reset animation"<<std::endl;
    
    if(animations[currentAnimation].reversed)
    {
        animations[currentAnimation].tick=animations[currentAnimation].row-1;
        animations[currentAnimation].currentcolumn=animations[currentAnimation].column-1;
        animations[currentAnimation].currentFrame=animations[currentAnimation].frames-1;
    }
    if(!animations[currentAnimation].reversed && !animations[currentAnimation].repeat)
    {
        animations[currentAnimation].tick=0;
        animations[currentAnimation].currentFrame=0;
        animations[currentAnimation].currentcolumn=animations[currentAnimation].startingcolumn;
        
        
        
        
    }
    
}
void Entity::animate()
{
    // might be a bug just below from spawnFragment class
        //////// Regular Idle Animations ///////////
        if(animations[currentAnimation].repeat && animations[currentAnimation].reversed==false) //player idle //or asteroid
        {
        
            setSource((animations[currentAnimation].width*animations[currentAnimation].tick)+(animations[currentAnimation].width*animations[currentAnimation].startingrow),(animations[currentAnimation].height*animations[currentAnimation].currentcolumn)+(animations[currentAnimation].height*animations[currentAnimation].startingcolumn),
                  animations[currentAnimation].width,
                  animations[currentAnimation].height);
            animations[currentAnimation].tick++;
            animations[currentAnimation].currentFrame++;
            if(animations[currentAnimation].tick>=animations[currentAnimation].row-1)
            {
                animations[currentAnimation].tick=0;
                animations[currentAnimation].currentcolumn++;
                if(animations[currentAnimation].currentcolumn>=animations[currentAnimation].column)
                {
                    animations[currentAnimation].currentcolumn=0;
                    animations[currentAnimation].currentFrame=0;
                    return;
                }
            
            }
        
        }
        
        /////////// End Regular Idle Animations //////////
       ///////// Entity explosion Animation //////
        if((animations[currentAnimation].repeat == false && !animations[currentAnimation].reversed)) // playOnce no rev repeat
        {
            
            setSource((animations[currentAnimation].width*animations[currentAnimation].tick)+(animations[currentAnimation].width*animations[currentAnimation].startingrow),(animations[currentAnimation].height*animations[currentAnimation].currentcolumn),
                      animations[currentAnimation].width,
                      animations[currentAnimation].height);
            
            animations[currentAnimation].tick++;
            animations[currentAnimation].currentFrame++;
            if(animations[currentAnimation].tick>=animations[currentAnimation].row)
            {
                animations[currentAnimation].tick=0;
                animations[currentAnimation].currentcolumn++;
            }
            if(animations[currentAnimation].currentFrame>=animations[currentAnimation].frames-1 && animations[currentAnimation].stopOnFinal )
            {
              
                animations[currentAnimation].currentFrame=animations[currentAnimation].frames-1;
                animations[currentAnimation].tick=animations[currentAnimation].row-1;
                animations[currentAnimation].currentcolumn=animations[currentAnimation].column-1;
            }
            if(animations[currentAnimation].currentFrame>=animations[currentAnimation].frames-1 && !animations[currentAnimation].stopOnFinal )
            {
                std::cout<<"Entity setting active to false"<<std::endl;
                this->setActive(false);
              
            }
            
        }
}
    

void Entity::animateEntity()
{
    checkSpeed();
 
        
        if((animations[currentAnimation].repeat == false && !animations[currentAnimation].reversed)) // playOnce no rev repeat
        {
            
            setSource((animations[currentAnimation].width*animations[currentAnimation].tick)+(animations[currentAnimation].width*animations[currentAnimation].startingrow),(animations[currentAnimation].height*animations[currentAnimation].currentcolumn),
                      animations[currentAnimation].width,
                      animations[currentAnimation].height);
            
            animations[currentAnimation].tick++;
            animations[currentAnimation].currentFrame++;
            if(animations[currentAnimation].tick>=animations[currentAnimation].row)
            {
                animations[currentAnimation].tick=0;
                animations[currentAnimation].currentcolumn++;
            }
            if(animations[currentAnimation].currentFrame>=animations[currentAnimation].frames-1 && animations[currentAnimation].stopOnFinal )
            {
        
                animations[currentAnimation].currentFrame=animations[currentAnimation].frames-1;
                animations[currentAnimation].tick=animations[currentAnimation].row-1;
                animations[currentAnimation].currentcolumn=animations[currentAnimation].column-1;
            }
            if(animations[currentAnimation].currentFrame>=animations[currentAnimation].frames-1 && !animations[currentAnimation].stopOnFinal )
            {
             /*   if(entityType==ASTEROID)
                {
                    this->setActive(false);
                } */
           /*     resetAnimation();  ///need to fix this. its rapidly calling reset animation for some reason when idle
                if(isReady())
                {
                    setCurrentAnimation(4); //when finished go back to ready state
                }
                else
                {
                    setCurrentAnimation(0);  //id 0 is playerIdle
                    
                }
                */
            }
            
        }
        if(animations[currentAnimation].repeat && animations[currentAnimation].reversed==false) //player idle //or asteroid
        {
            
            setSource((animations[currentAnimation].width*animations[currentAnimation].tick)+(animations[currentAnimation].width*animations[currentAnimation].startingrow),(animations[currentAnimation].height*animations[currentAnimation].currentcolumn)+(animations[currentAnimation].height*animations[currentAnimation].startingcolumn),
                      animations[currentAnimation].width,
                      animations[currentAnimation].height);
            animations[currentAnimation].tick++;
            animations[currentAnimation].currentFrame++;
            if(animations[currentAnimation].tick>=animations[currentAnimation].row-1)
            {
                animations[currentAnimation].tick=0;
                animations[currentAnimation].currentcolumn++;
                if(animations[currentAnimation].currentcolumn>=animations[currentAnimation].column)
                {
                    animations[currentAnimation].currentcolumn=0;
                    animations[currentAnimation].currentFrame=0;
                    return;
                }
                
            }
            
        }
        if(animations[currentAnimation].reversed && !animations[currentAnimation].repeat)
        {
            
            
            setSource((animations[currentAnimation].width*animations[currentAnimation].tick)+(animations[currentAnimation].width*animations[currentAnimation].startingrow),(animations[currentAnimation].height*animations[currentAnimation].currentcolumn)+(animations[currentAnimation].height*animations[currentAnimation].startingcolumn),
                      animations[currentAnimation].width,
                      animations[currentAnimation].height);
            animations[currentAnimation].tick--;
            animations[currentAnimation].currentFrame--;
            if(animations[currentAnimation].tick<=0)
            {
                animations[currentAnimation].currentcolumn--;
                animations[currentAnimation].tick=animations[currentAnimation].row-1;
            }
            if(animations[currentAnimation].currentcolumn<=0)
            {
                animations[currentAnimation].tick=0;
                animations[currentAnimation].currentFrame=0;
                animations[currentAnimation].currentcolumn=0;
           //     setGettingReady(false);
           //     setReady(false);
                setCurrentAnimation(0);
            }
        }
        else
        {
            return;
        }
}

void Entity::setXAcc(float xAcc)
{
    this->xAcc=xAcc;
}
void Entity::setYAcc(float yAcc)
{
    this->yAcc=yAcc;
}
void Entity::setMaxAcc(float maxAcc)
{
    this->maxAcc=maxAcc;
}
void Entity::setDefaultAcc(float accel)
{
    this->defaultAcc=accel;
}
void Entity::setMass(int m)
{
    this->mass = m;
}

