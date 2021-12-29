//
//  gamestate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef gamestate_hpp
#define gamestate_hpp

#include <stdio.h>
#include "game.hpp"

class GameState
{
public:
    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void clean() = 0;
    
    virtual void pause() = 0;
    virtual void resume() = 0;
    
    virtual void handleEvents(Game* game) = 0;
    virtual void update(Game* game) = 0;
    virtual void draw(Object &object,int rotationAngle) =0;
    virtual void render(Game* game) = 0;
    
    //   void changeState(Game* game, GameState* state)
    //   {
    //      game->changeState(state);
    //  }
    
protected:
    GameState() {
        
    }
};
#endif /* gamestate_hpp */
