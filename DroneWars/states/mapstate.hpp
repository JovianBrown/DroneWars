//
//  mapstate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef mapstate_hpp
#define mapstate_hpp

#include <stdio.h>
#include "gamestate.hpp"
#include "player.hpp"

class MapState : public GameState
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
    static MapState* instance()
    {
        return &m_MapState;
    }
    
    protected:
    
    MapState() {}
    
private:
    static MapState m_MapState;
    
    SDL_Renderer* mapRenderer;
    Object map;
    Player player;
};
#endif /* mapstate_hpp */
