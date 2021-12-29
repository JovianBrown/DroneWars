//
//  timer.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/17.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
//used in playstate for deciding when to end the level and when to spawn enemies

class Timer
{
public:
    Timer()
    :startTime(getCurrentTime()),duration(7000),active(false),repeatTimer(false)
    {
        std::cout<<"initated timer"<<std::endl;
    }
    Timer(int duration)
    :startTime(getCurrentTime()),active(true)
    {
        
        this->duration=duration;
    }
    
    int getCurrentTime()
    {
        return SDL_GetTicks();
    }
    bool isActive()
    {
        return active;
    }
    bool repeat()
    {
        return repeatTimer;
    }
    int getTimeLeft()
    {
        int timeLeft = (startTime+duration)-currentTime;
        return timeLeft;
    }
    void setStartTime(int time)
    {
        startTime=time;
    }
    void setRepeat(bool b);
    void update();
    void setTimerActive(bool b);
    void setDuration(int time)
    {
        std::cout<<"Duration set to "<<time<<std::endl;
        duration = time;
    }
private:
    int startTime,duration,currentTime;
    bool active;
    bool repeatTimer;
};
#endif /* timer_hpp */
