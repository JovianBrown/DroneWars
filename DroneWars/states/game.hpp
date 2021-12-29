//
//  game.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#pragma once
#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <vector>
#include "object.hpp"

class GameState; // make sure this class knows about the GameState class.

class Game
{
public:
    
    Game();
    
    void init(const char* title, int width, int height,bool fullscreen);
    void setPaused(bool b);
    bool isPaused();
    void changeState(GameState* state);
    void pushState(GameState* state);
    void popState();
    void handleEvents(); // remove pointer to game class
    void update();
    void render();
    void clean();
    SDL_Renderer* getRenderer()
    {
        return renderer;
    }
    bool running()
    {
        return m_bRunning;
        
    }
    bool paused()
    {
        return m_Paused;
        
    }
    void quit() {
        m_bRunning = false;
        
    }
    SDL_Surface* getScreen()
    {
        return m_pScreen;
        
    }
    
    
private:
    
    // the stack of states
    std::vector<GameState*> states;
    
    SDL_Surface* m_pScreen;
    bool m_bFullscreen;
    bool m_bRunning;
    bool m_Paused;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    
};

#endif /* game_hpp */
