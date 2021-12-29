//
//  timer.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/17.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "timer.hpp"
//
//  timer.cpp
//  DroneWars
//
//  Created by Jovian on 2021/11/29.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "timer.hpp"

void Timer::update()
{
    
    currentTime=SDL_GetTicks();
    if(currentTime>=duration+startTime && isActive())
    {
        setTimerActive(false);
        return;
    }
    if(currentTime>=duration+startTime && repeat())
    {
        std::cout<<"calling timer repeat"<<std::endl;
        setStartTime(currentTime);
        
    }
}
void Timer::setRepeat(bool b)
{
    repeatTimer=b;
}

void Timer::setTimerActive(bool b)
{
    active=b;
}

