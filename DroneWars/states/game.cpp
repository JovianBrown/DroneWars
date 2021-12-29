//
//  game.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "game.hpp"
#include "gamestate.hpp"

Game::Game()
{
    
}

void Game::init(const char* title, int width, int height,bool fullscreen)
{
    // initialize SDL
    SDL_PLATFORM_SUPPORTS_METAL;
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    SDL_Init(SDL_INIT_EVERYTHING);
    
    
    m_bFullscreen = fullscreen;
    if(m_bFullscreen == true)
    {
        //  window = SDL_CreateWindow(title, 0 , 0 , width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN |//SDL_WINDOW_METAL );
        window = SDL_CreateWindow(title, 0 , 0 , width, height, SDL_WINDOW_FULLSCREEN |SDL_WINDOW_METAL );
        
    }
    else
    {
        window = SDL_CreateWindow(title, 0 , 0 , width, height, SDL_WINDOW_METAL );
        
    }
    
    //   renderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_RenderGetMetalLayer(renderer);
    SDL_GL_SetSwapInterval(-1);
    
    m_bRunning = true;
    m_Paused = false;
    printf("Game Initialized Successfully\n");
    
    
}

/*
 cleans previous state if not empty, then pushes new state onto stack
 */
void Game::changeState(GameState* state)
{
    // cleanup the current state
    if ( !states.empty() ) {
        states.back()->clean();
        states.pop_back();
    }
    
    // store and init the new state
    states.push_back(state);
    states.back()->init(renderer);
}

/*
 Whereas ChangeState() pushes a state onto the stack and removes the previous state, PushState() pauses the previous state before pushing a new state onto the stack, this state can then be removed and the previous state resumed. Extrememly useful for pausing.
 */
void Game::pushState(GameState* state)
{
    // pause current state
    if ( !states.empty() ) {
        states.back()->pause();
    }
    
    // store and init the new state
    states.push_back(state);
    states.back()->init(renderer);
}

/*
 Remove and resume previous state.
 */
void Game::popState()
{
    // cleanup the current state
    if ( !states.empty() )
    {
        states.back()->clean();
        states.pop_back();
    }
    
    // resume previous state
    if ( !states.empty() )
    {
        
        states.back()->resume();
    }
}


void Game::handleEvents()
{
    // let the state handle events
    states.back()->handleEvents(this);
}


void Game::update()
{
    // let the state update the game
    states.back()->update(this);
}

void Game::render()
{
    
    
    states.back()->render(this);
    
}
void Game::setPaused(bool b)
{
    m_Paused = b;
}
bool Game::isPaused()
{
    return m_Paused;
}
void Game::clean()
{
    while ( !states.empty() )
    {
        states.back()->clean();
        states.pop_back();
    }
    
    // shutdown SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_VideoQuit();
    SDL_Quit();
}
