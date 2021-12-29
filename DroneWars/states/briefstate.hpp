//
//  briefstate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef briefstate_hpp
#define briefstate_hpp

#include <stdio.h>
#include "gamestate.hpp"
#include "missionbriefgui.hpp"
#include "player.hpp"
class BriefState : public GameState
{
    public:
    void init(SDL_Renderer* renderer);
    void clean();
    
    void pause();
    void resume();
    void handleEvents(Game* game);
    void update(Game* game);
    void draw(Object &object,int rotationAngle);
    void render(Game* game);
    static BriefState* instance()
    {
        return &m_briefState;
    }
    void loadMissionBriefing(Player* player);   // load the mission brief string from a file based on ID #
protected:
    
    BriefState() {}
    
private:
    static BriefState m_briefState;
    SDL_Renderer* briefRenderer;
    MissionBriefGUI missionBriefGUI;
    std::vector <std::string> missionBriefing;
    std::string levelBrief;
    std::string longString;
    std::vector<std::string> shortStrings;
    Player* activePlayer;
};
#endif /* briefstate_hpp */
