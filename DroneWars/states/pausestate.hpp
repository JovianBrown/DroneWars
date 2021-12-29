//
//  pausestate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef pausestate_hpp
#define pausestate_hpp

#include <stdio.h>
#include "gamestate.hpp"
class PauseState : public GameState
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
    static PauseState* instance()
    {
        return &m_PauseState;
    }
    
protected:
    
    PauseState() {}
    
private:
    static PauseState m_PauseState;
    
    SDL_Renderer* pauseRenderer;
};



#endif /* pausestate_hpp */
