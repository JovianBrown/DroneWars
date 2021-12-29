//
//  briefstate.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "briefstate.hpp"
#include "menustate.hpp"
#include "playstate.hpp"
#include <iostream>
#include <fstream>
#include <string>
BriefState BriefState::m_briefState;

void BriefState::init(SDL_Renderer *renderer)
{
    briefRenderer = renderer;
    int windowWidth = 1280;
    int windowHeight = 800;
    missionBriefGUI.init(briefRenderer);
    missionBriefGUI.initGUI(windowWidth, windowHeight);
    std::string line;
    std::ifstream myfile ("brief.txt");
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            missionBriefing.push_back(line);
        }
        myfile.close();
    }
    
    else std::cout << "Unable to open brief.txt";
}
void BriefState::update(Game *game)
{
    
}

void BriefState::handleEvents(Game* game)
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
                    game->changeState(MenuState::instance());
                    break;
                case SDLK_SPACE:
                    game->changeState(PlayState::instance());
                   // game->pushState(PlayState::instance());

                    PlayState::instance()->loadPlayer(activePlayer);
                    break;
            }
        }
    }
        
}
void BriefState::draw(Object &object, int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(briefRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
   //missionBriefGUI.drawText(briefRenderer,"Your mission if you choose to accept it.", 200, 200, 255, 255, 255);
}
void BriefState::render(Game *game)
{
    SDL_SetRenderDrawColor(briefRenderer, 0, 0, 0, 255);
    SDL_RenderClear(briefRenderer);

    draw(missionBriefGUI,0);
    unsigned int  j = 0;   //below breaks up brief txt line into smaller bits of 80 bytes so it wraps to screen
    for ( unsigned int i = 0; i < levelBrief.length(); i += 80 )
    {
        shortStrings.push_back( levelBrief.substr( i, 80 ) );
        missionBriefGUI.drawText(briefRenderer,levelBrief.substr( i, 80 ).c_str(), missionBriefGUI.getDestination().x+30, (missionBriefGUI.getDestination().y+10)+j*15, 255, 255, 255);
        j++;
    }

    SDL_RenderPresent(briefRenderer);
}
void BriefState::loadMissionBriefing(Player* player)
{
    activePlayer = player;
    int level = activePlayer->getLevel();
    levelBrief = missionBriefing[level-1];
  
}
void BriefState::resume()
{
    
}

void BriefState::pause()
{
    
}

void BriefState::clean()
{
 //   SDL_DestroyTexture(missionBriefGUI.getTexture());
    missionBriefGUI.~MissionBriefGUI();
    missionBriefGUI.clean();
}
