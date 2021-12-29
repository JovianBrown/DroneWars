//
//  main.cpp
//  DroneWars
//
//  Created by mac on 2021/12/27.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include <iostream>
#include "game.hpp"
#include "menustate.hpp"
int main(int argc, char *argv[]) {
    Game game;
    const int windowWidth = 1280;
    const int windowHeight = 800;
    const int FPS =60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    
    game.init("DroneWars v0.3", windowWidth, windowHeight, false);
    game.changeState(MenuState::instance());
    
    
    while(game.running())
    {
        frameStart = SDL_GetTicks();
        
        game.handleEvents();
        game.update();
        game.render();
        
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }
    
    // cleanup the engine
    game.clean();
    return 0;
}
