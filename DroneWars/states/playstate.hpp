//
//  playstate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef playstate_hpp
#define playstate_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include "game.hpp"
#include "gamestate.hpp"
#include "background.hpp"
#include "player.hpp"
#include "hud.hpp"
#include "item.hpp"
#include "projectile.hpp"
#include "timer.hpp"
#include "soundfx.hpp"
#include "dockstate.hpp"
#include "savegame.hpp"

class PlayState : public GameState
{
public:
    void init(SDL_Renderer* renderer);
    void clean();
    void pause();
    void resume();
    void handleEvents(Game* game);
    void update(Game* game);
    void render(Game* game);
    void checkBorders(Entity &object);
    void draw(Object &object,int rotationAngle);
    void drawBackground(Background &background);
    void loadPlayer(Player* p);
    static PlayState* instance()
    {
        return &m_PlayState;
    }
    
protected:
    
    PlayState()
    {
    }
    
private:
    static PlayState m_PlayState;
    Background background;
    SDL_Renderer* playRenderer;

    ///////// Player stuff //////////
 
    Player* player;    //player should be a pointer
    std::vector <Entity> playerAnimations;
    int playerIdle;
    int playerReady;  //player getting ready
    int playerReadyReversed;
    int playerShield;
    Projectile playersBullet;
    std::vector <Projectile> playersBullets;
    //////////////// End player stuff///////////
    Entity asteroid;
    std::vector <Entity> asteroidAnimations;
    std::vector <Entity> asteroids;
    int asteroidIdle;
    int asteroidExplode;
    //////////////
    ///////Level and BG stuff//////
    Hud hud;
    int* levelH=nullptr;
    int levelHeight;
    int windowWidth,windowHeight;
    Uint16 lastFrame;
    Uint16 frameCount;
    Timer asteroidTimer;
    //Timer levelTimer;
    Timer* levelTimer=nullptr;
    Soundfx sfx;
    std::vector<std::string> levelInfo;
    std::vector<std::string> texturePaths;
    /////////////end Level BG stuff///////
    ////// Items /////
    Item rareElement;
    Item energyPulse;
    Item preciousMetal;

    std::vector<Item> items;
   
    ///// Items End //////
    void spawnItem(int x, int y);
    void spawnAsteroid();
    void spawnFragment(Entity asteroid);
    bool checkCollision(SDL_Rect A, SDL_Rect B);
    void playerFire();
    void loadLevel(int levelNumber);
};

#endif /* playstate_hpp */
