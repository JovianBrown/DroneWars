//
//  pausestate.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "pausestate.hpp"
PauseState PauseState::m_PauseState;

void PauseState::init(SDL_Renderer* renderer)
{
    // pauseRenderer= renderer;
    
    printf("PauseState Init Successful\n");
}

void PauseState::clean()
{
    printf("PauseState Clean Successful\n");
}

void PauseState::resume()
{
    
}

void PauseState::pause()
{
    std::cout<<"Paused state"<<std::endl;
}

void PauseState::handleEvents(Game *game)
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
            {
                case SDLK_SPACE:
                    game->setPaused(false);
                    game->popState();
                    break;
            }
                
        }
    }
}

void PauseState::update(Game* game)
{
    
}


void PauseState::draw(Object &object,int rotationAngle)
{
    
}

void PauseState::render(Game* game)
{
    SDL_SetRenderDrawColor(pauseRenderer, 255, 255, 255, 255);
    
    
    
    
    SDL_RenderClear(pauseRenderer);
    //draw here
    
    SDL_RenderPresent(pauseRenderer);
}
