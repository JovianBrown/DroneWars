//
//  mapstate.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "mapstate.hpp"
#include "dockstate.hpp"
MapState MapState::m_MapState;

void MapState::init(SDL_Renderer* renderer)
{
     mapRenderer= renderer;    
    map.setImage("res/map1.png", mapRenderer);
    map.setSource(0, 0, 1920, 1280);
    map.setDestination(280, 100, 1920/3, 1280/3);   ///need to set according to screen width and height
    player.init(mapRenderer);
    player.setDestination(0, 0, 80 , 80);
    printf("MapState Init Successful\n");
}



void MapState::resume()
{
    
}

void MapState::pause()
{
    std::cout<<"Paused state"<<std::endl;
}

void MapState::handleEvents(Game *game)
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
                case SDLK_q:
                    game->changeState(DockState::instance());
                    break;
            }
        }
    }
}

void MapState::update(Game* game)
{
    
}


void MapState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(mapRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}

void MapState::render(Game* game)
{
    SDL_SetRenderDrawColor(mapRenderer, 0, 0, 0, 255);

    
    SDL_RenderClear(mapRenderer);
    //draw here
    draw(map,0);
    draw(player,0);
    SDL_RenderPresent(mapRenderer);
}
void MapState::clean()
{
    SDL_DestroyTexture(map.getTexture());
    SDL_DestroyTexture(player.getTexture());
    printf("MapState Clean Successful\n");
}
