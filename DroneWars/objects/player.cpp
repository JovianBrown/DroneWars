//
//  player.cpp
//  DroneWarsV3
//
//  Created by Jovian on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "player.hpp"


void Player::loadSaveGame()
{
    
}

void Player::init(SDL_Renderer* renderer)
{
    setImage("res/dronev2spriteallpng.png", renderer);
    setSource(0, 0, 300, 300);
    setDestination(100, 500, 200, 200);
    int playerMass = 40;
    setMass(playerMass); //40 kg
    setDefaultAcc(100);
    setMaxShield(100);
/*    setHps(100);
    setMaxHps(100);
    setEnergy(100);
    setMaxEnergy(100);
    setShield(100);
    setMaxShield(100);
    setRareElements(0);
    setPreciousMetals(0);
    setCurrentLevel(1); */

}
void Player::animatePlayer()
{        
        //////// Regular Idle Animations ///////////
        if(animations[currentAnimation].repeat && animations[currentAnimation].reversed==false) //idle animations
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
                   setReady(true);
                   setGettingReady(false);
                animations[currentAnimation].currentFrame=animations[currentAnimation].frames-1;
                animations[currentAnimation].tick=animations[currentAnimation].row-1;
                animations[currentAnimation].currentcolumn=animations[currentAnimation].column-1;
            }
            if(animations[currentAnimation].currentFrame>=animations[currentAnimation].frames-1 && !animations[currentAnimation].stopOnFinal )
            {
                if(currentAnimation==3 && isReady())
                {
                    resetAnimation();
                    currentAnimation=1; //ready anim
                    return;
                }
                if(currentAnimation==3 && !isReady())
                {
                    currentAnimation=0; //not ready animation
                    return;
                }
                if(isReady())
                {
                    currentAnimation=2; //when finished go back to ready state
                }
                else
                {
                    currentAnimation=0;  //id 0 is playerIdle
                    std::cout<<"set current animation to 0 "<<std::endl;
                }
            
            }
            
        }
        if(animations[currentAnimation].reversed && !animations[currentAnimation].repeat)
        {
            std::cout<<"calling reverse animation not repeat"<<std::endl;
            
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
                setGettingReady(false);
                setReady(false);
                setCurrentAnimation(0);
            }
        }
}
void Player::setGettingReady(bool b)
{
    this->gettingReady = b;
}

void Player::setReady(bool b)
{
    this->ready=b;
}
void Player::setEnergy(int e)
{
    
    this->energy = e;
}

void Player::setRareElements(int re)
{
    this->rareElements = re;
}

void Player::setPreciousMetals(int p)
{
    this->preciousMetals= p;
}

void Player::setMaxEnergy(int e)
{
    this->maxEnergy = e;
}

void Player::setMaxShield(int s)
{
    this->maxShield = s;
}
void Player::setScore(int s)
{
    this->score = s;
}

void Player::setShield(int s)
{
    this->shield = s;
}
void Player::setCurrentLevel(int level )
{
    this->currentLevel = level;
}
void Player::setCredits(int c)
{
    this->credits = c;
}

void Player::setCurrentWeapon(int w)
{
    this->currentWeapon = w;
}
