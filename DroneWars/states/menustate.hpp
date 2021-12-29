//
//  menustate.hpp
//  DroneWarsV3
//
//  Created by Jovian on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef menustate_hpp
#define menustate_hpp

#include <stdio.h>
#include "gamestate.hpp"
#include <SDL2/SDL.h>
#include "game.hpp"
#include "hud.hpp"
#include "menugui.hpp"
#include "player.hpp"
#include "loadgame.hpp"

class MenuState : public GameState
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
    
    // Implement Singleton Pattern
    static MenuState* instance()
    {
        return &m_MenuState;
    }
    
protected:
    
    MenuState() {}
    
private:
    static MenuState m_MenuState;
    Object splashScreen;
    SDL_Renderer* menuRenderer;
    MenuGUI menuGUI;
    Player* player; //for a new player object which will be used in the next state
    Player* createNewPlayer();
};

#endif /* menustate_hpp */
