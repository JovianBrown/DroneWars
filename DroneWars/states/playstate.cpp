//
//  playstate.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "playstate.hpp"
#include "pausestate.hpp"
#include "loadgame.hpp"
#define DEAD_ZONE 3200
//original dead_zone 3200

PlayState PlayState::m_PlayState;


void PlayState::init(SDL_Renderer* renderer)
{
    if(levelTimer==NULL)
    {
        levelTimer = new Timer;
    }
    playRenderer = renderer;
    //////// Level Stuff///////////////
    levelHeight= 1280;
    levelH = &levelHeight;
    windowWidth = 1280;
    windowHeight = 800;

    //////////// for specific levels /////////
    
    background.setImage("res/starsBG640.png", playRenderer);
    background.setSource(0, 0, windowWidth, windowHeight);
    background.setDestination(0, 0, 1280, 1280);
    
    

    ///////////////////////////
    
    sfx.addSound("res/audio/fire.wav"); //player fire sound
    sfx.addSound("res/audio/asteroidexplode.wav");
    sfx.addSound("res/audio/alert.wav");
    
    ////////// End Level stuff//////////


   
    ///////// end player stuff ///////
    
    ////////// Init Other Entities /////////
    asteroid.setImage("res/asteroidspritesheet.png", playRenderer);
    asteroid.setSource(0, 0, 200, 200);
    asteroidIdle = asteroid.createCycle(8, 3, 0, 0, 200, 200, 30, true, false, false);
    asteroidExplode = asteroid.createCycle(8, 3, 0, 3, 200, 200, 10, false, false,false);
    //////////// End Init Other Entities ///////// Like asteroids ////
    hud.initHud(playRenderer, windowWidth, windowHeight);
    /////////////// Load ITEMS//////////
    energyPulse.init(playRenderer, ENERGY_PULSE);
    preciousMetal.init(playRenderer,PRECIOUS_METAL);
    rareElement.init(playRenderer, RARE_ELEMENT);

    
    ///////////////Load Items End//////////
    

    printf("PlayState Init Successful\n");
    
    

}
void PlayState::loadLevel(int levelNumber)
{
    int level = levelNumber;
    std::string s_level = std::to_string(level);
    std::string levelName = "level";
    std::string extension = ".txt";
    std::string line;
    std::string concatenated = levelName+s_level+extension;
    std::ifstream levelFile (concatenated);
    std::cout<<"-- "<<concatenated<<" info: "<<std::endl;
    if (levelFile.is_open())
    {
        while ( getline (levelFile,line) )
        {
            levelInfo.push_back(line);
            std::cout << line << '\n';
        }
        levelFile.close();
        

        levelTimer= new Timer;
        levelTimer->setDuration(stoi(levelInfo[0]));
        levelTimer->setTimerActive(true);

        if(stoi(levelInfo[1])>0)   //asteroid bool yes
        {
            asteroidTimer.setDuration(stoi(levelInfo[2])); //3rd line in level file should have duration for asteroid timer
            asteroidTimer.setTimerActive(true);
        }
        int numberOfTextures = stoi(levelInfo[3]);
        int startTextureRow=4;
        if(numberOfTextures>0)
        {
            for(int i = 0;i<numberOfTextures;i++)
            {
                texturePaths.push_back(levelInfo[startTextureRow+i]);
                std::cout<<"Pushed Back texture: "<<levelInfo[startTextureRow+i]<<std::endl;
            }
        }
        
        
    }
    else std::cout << "Unable to open level!"<<std::endl;

 
    
}
void PlayState::spawnItem(int x, int y)
{
    cout<<"Spawned Item "<<endl;
    if(items.size()>50)
    {
        items.erase(items.begin(),items.begin()+30);

    }
    int randomItem = rand()%9;
    if(randomItem<3)
    {
        rareElement.setActive(true);
        rareElement.setDestination(x, y, 100, 100);
        items.push_back(rareElement);
    }
    if(randomItem>=3 && randomItem <= 6)
    {
        preciousMetal.setActive(true);
        preciousMetal.setDestination(x, y, 100, 100);
        items.push_back(preciousMetal);
    }
    if(randomItem>6)
    {
        energyPulse.setActive(true);
        energyPulse.setDestination(x, y, 100, 100);
        items.push_back(energyPulse);
        
    }
}
void PlayState::spawnAsteroid()
{
    if(asteroids.size()>=100)
    {
        asteroids.erase(asteroids.begin(),asteroids.begin()+70);
        std::cout<<"cleared asteroid stack, asteroids size: "<<asteroids.size()<<std::endl;
        
    }
    int randomMass = rand()%100+1;
    int randomX = rand()%windowWidth;
    int randomRotation = rand()%180;
    int randomSpeed = (rand()%5)+5;
    asteroid.setMass(randomMass);
    if(randomMass< 33 && randomMass > 0)
    {
        asteroid.setDestination(randomX, 0, 33, 33);
        asteroid.setHps(10);
    }
    if(randomMass<= 66 && randomMass>=33)
    {
        asteroid.setDestination(randomX, 0, 66, 66);
        asteroid.setHps(30);
        
    }
    if(randomMass>66 && randomMass<=100)
    {
        asteroid.setDestination(randomX, 0, 100, 100);
        asteroid.setHps(55);
        
    }
    asteroid.setActive(true);
    asteroid.setRotationAngle(randomRotation);
    asteroid.setYAcc(randomSpeed);
    asteroid.setXAcc(0);

    asteroids.push_back(asteroid);
    
}
void PlayState::spawnFragment(Entity asteroid)
{
    if(asteroids.size()>=100)
    {
        asteroids.erase(asteroids.begin(),asteroids.begin()+70);
        std::cout<<"cleared asteroid stack, asteroids size: "<<asteroids.size()<<std::endl;
        
    }
    int randomMass = rand()%20+1;
    int randomRotation = rand()%180;
    int randomSpeed = (rand()%10)+5;
    asteroid.setMass(randomMass);
    
    asteroid.setDestination(asteroid.getDestination().x, asteroid.getDestination().y, 10, 10);
    asteroid.setHps(5);
   
    asteroid.setActive(true);
    asteroid.setRotationAngle(randomRotation);
    asteroid.setYAcc(randomSpeed);
    asteroid.setXAcc(randomSpeed);

    asteroids.push_back(asteroid);
    
}

void PlayState::playerFire()
{
    sfx.playSound(0);
    playersBullet.setActive(true);
    playersBullet.setDestination((player->getDestination().x+(player->getDestination().w/2)-(playersBullet.getDestination().w/2)), player->getDestination().y+(player->getDestination().h/2), playersBullet.getDestination().w, playersBullet.getDestination().h);
    playersBullets.push_back(playersBullet);
    if(playersBullets.size()>100)
    {
        playersBullets.clear();
    }
}
void PlayState::loadPlayer(Player* p) //should be called from either MenuState or DockState
{
   // Loadgame loadGame;
   // std::vector<string> playerStats = loadGame.getPlayerStats();
    player = p;
    player->init(playRenderer);
    playerIdle = player->createCycle(8, 2, 8, 0, 300, 300, 30, true, false, false); //id0
    playerReady = player->createCycle(8,3,0,0,300,300,30,false,false,true);//id1
    playerReadyReversed = player->createCycle(8,3,0,0,300,300,30,0,true,true); //id2
    playerShield = player->createCycle(8, 2, 0, 3, 300, 300, 30, false, false, false); //id3
    player->setCurrentAnimation(playerIdle);
    loadLevel(player->getLevel());
    ////players bullet needs to use info from loadPlayer to determine what is the current weapon
     playersBullet.init(player->getCurrentWeapon(), playRenderer); //0 is for SMALL_BLUE_LASER 1 is for WIDE_BLUE_LASER
    
}
void PlayState::pause()
{
    printf("PlayState Paused\n");
}

void PlayState::resume()
{
    printf("PlayState Resumed\n");
}

void PlayState::handleEvents(Game* game)
{
    
    SDL_Event event;
    
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        { /*
            case SDL_JOYAXISMOTION :
                if (event.jaxis.axis == 0)
                {
                    if (event.jaxis.value < -DEAD_ZONE)
                    {
                        player->applyForce(player->getDefaultAcc(),WEST);
                    }
                    
                    else if (event.jaxis.value > DEAD_ZONE)
                    {
                        player->applyForce(player->getDefaultAcc(),EAST);
                    }
                    
                 
                }
                
                if (event.jaxis.axis == 1)
                {
                    if (event.jaxis.value < -DEAD_ZONE)
                    {
                        player->applyForce(player->getDefaultAcc(),NORTH);
                    }
                    
                    else if (event.jaxis.value > DEAD_ZONE)
                    {
                        player->applyForce(player->getDefaultAcc(),SOUTH);
                    }
                    
                   
                }
                break;
            case SDL_JOYBUTTONDOWN:
                printf("button: %i\n", event.jbutton.button);
                if(player->isReady())
                {
                    playerFire();
                    
                    break;
                }
                else
                {
                    std::cout<<"notReady"<<std::endl;
                    break;
                }
                break; */
            case SDL_QUIT:
                game->quit();
                break;
                
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_q:
                        game->changeState(MenuState::instance());
                        break;
                    case SDLK_w:
                        player->applyForce(player->getDefaultAcc(),NORTH);
                        break;
                    case SDLK_s:
                        player->applyForce(player->getDefaultAcc(),SOUTH);
                        break;
                    case SDLK_a:
                        player->applyForce(player->getDefaultAcc(),WEST);
                        break;
                    case SDLK_d:
                        player->applyForce(player->getDefaultAcc(),EAST);
                        break;
                    case SDLK_SPACE:
                        if(player->isReady())
                        {
                            playerFire();
                      
                            break;
                        }
                        else
                        {
                            std::cout<<"notReady"<<std::endl;
                            break;
                        }
                    case SDLK_o:
                        if(!player->isReady())
                        {
                            player->setCurrentAnimation(playerReady);
                            player->resetAnimation();
                            std::cout<<"notReady"<<std::endl;
                            player->setGettingReady(true);
                            return;
                        }
                        else
                        {
                            player->setCurrentAnimation(playerReadyReversed);
                            player->resetAnimation();
                            std::cout<<"ready"<<std::endl;
                            
                        }
                        break;
                    case SDLK_p:
                        game->setPaused(true);
                        game->pushState(PauseState::instance());
                        break;
                }
                
        }
    } 
}
void PlayState::checkBorders(Entity &object)
{
    if(object.getDestination().x>(windowWidth-object.getDestination().w))
    {
        object.setDestination(windowWidth-object.getDestination().w, object.getDestination().y, object.getDestination().w, object.getDestination().h);
        object.setXAcc(-1.0);
    }
    if(object.getDestination().y>(windowHeight-object.getDestination().h))
    {
        object.setDestination(object.getDestination().x, windowHeight-object.getDestination().h, object.getDestination().w, object.getDestination().h);
        object.setYAcc(0.0);
        
    }
    if(object.getDestination().y <= 0)
    {
        std::cout<<"Object Destination Y : "<<object.getDestination().y<<std::endl;
        object.setDestination(object.getDestination().x, 0, object.getDestination().w, object.getDestination().h);
        object.setYAcc(1.0);
    }
    if(object.getDestination().x <= 0)
    {
        object.setDestination(0, object.getDestination().y, object.getDestination().w, object.getDestination().h);
        object.setXAcc(1.0);
        
    }
}

void PlayState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(playRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}
bool PlayState::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = rectA.x;
    rightA = rectA.x + rectA.w;
    topA = rectA.y;
    bottomA = rectA.y + rectA.h;
    
    //Calculate the sides of rect B
    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = rectB.y + rectB.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
} 
void PlayState::drawBackground(Background &background)
{
    SDL_Rect destination = background.getDestination();
    SDL_Rect source = background.getSource();  //need to set this as a constant
    SDL_Rect destination2;
    destination2.h=destination.h;
    destination2.w=destination.w;
    destination2.x=destination.x;
    destination2.y=destination.y-1280;
    
    SDL_Rect source2 = background.getSource();
    SDL_RenderCopyEx(playRenderer,background.getTexture(),&source,&destination,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(playRenderer,background.getTexture(),&source2,&destination2,0,NULL,SDL_FLIP_NONE);
    
}
void PlayState::update(Game* game)
{
    if(!game->isPaused())
    {
        background.update(*levelH);
        player->update();
        player->animatePlayer();
        asteroidTimer.update();
        if(!asteroidTimer.isActive())
        {
            spawnAsteroid();
            asteroidTimer.setStartTime(SDL_GetTicks());
            asteroidTimer.setTimerActive(true);
            
        }
        levelTimer->update();
        if(!levelTimer->isActive())
        {
            player->setCurrentLevel(player->getLevel()+1);
            Savegame sg(player);
            std::cout<<"level over you win ! yay"<<std::endl;
            
            game->changeState(DockState::instance());
           // break;
        }
        for(Projectile &p: playersBullets)
        {
            if(p.isActive())
            {
                p.update();

                if(p.getDestination().y<0)
                {
                    p.setActive(false);
                }
                for(Entity &a: asteroids)  //check collisions between asteroids and projectiles
                {
                    
                    if(checkCollision(p.getDestination(), a.getDestination()) && a.isActive())
                    {
                        
                        p.setActive(false);
                        a.setHps(a.getHps()-p.getDamage());
                        a.setYAcc(a.getYAcc()-1);
                    }
                }
            }
        }
        for(Entity &a: asteroids)
        {
            if(a.isActive())
            {
                a.update();
                a.animate();
                if(a.getHps()<1 && !a.didJustCollide())
                {
                    player->setScore(player->getScore()+10);
                    sfx.playSound(1);   ///asteroid explode
                    a.setJustCollided(true);  ///prevents the sound FX from being played more than once
                    a.setCurrentAnimation(asteroidExplode);
                    if(a.getMass()>30)
                    {
                     //   spawnFragment(a);

                    }
                    if(a.getMass()>75)
                    {
                        spawnItem(a.getDestination().x, a.getDestination().y);
                    }
                    
                }
                if(a.getDestination().y>windowHeight)
                {
                    a.setActive(false);
                }
                if(checkCollision(a.getDestination(), player->getDestination()) && !a.didJustCollide())
                {
                    int playerYAccelleration = (player->getMass()*player->getYAcc())+(a.getMass()*(a.getYAcc()));
                    int playerYSpeed = playerYAccelleration/player->getMass();
                    int playerXAccelleration =(player->getMass()*player->getXAcc())+(a.getMass()*(a.getXAcc()));
                    int playerXSpeed = playerXAccelleration/player->getMass();
                    
                    player->setYAcc(playerYSpeed);
                    player->setXAcc(playerXSpeed);
                    sfx.playSound(1); //asteroid explode
                    if(player->getHps()<(player->getMaxHps()/4))
                    {
                        sfx.playSound(2); ///alert sound
                    }
                    if(player->getHps()<1)
                    {
                        sfx.playSound(2); ///alert sound
                        std::cout<<"You lose!"<<std::endl;
                        game->changeState(MenuState::instance());
                        //player->setActive(false);
                        
                    }
                    int asteroidYAcceleration = (player->getMass()*player->getYAcc())+(a.getMass()*(a.getYAcc()));
                    int asteroidYSpeed = asteroidYAcceleration/a.getMass();
                    
                    int asteroidXAcceleration = (player->getMass()*player->getXAcc())+(a.getMass()*(a.getXAcc()));
                    int asteroidXSpeed = asteroidXAcceleration/a.getMass();
                    a.setYAcc(asteroidYSpeed);
                    a.setXAcc(asteroidXSpeed);
                    a.setJustCollided(true);
                    a.setCurrentAnimation(asteroidExplode);
                    if(player->getShield()>0)
                    {
                        player->setShield(player->getShield()-a.getMass());
                        player->setCurrentAnimation(playerShield);
                        
                    }
                    else
                    {
                        player->setHps(player->getHps()-a.getMass());
                    }
                    return;
                }
            }
        }
        //// Update Items  /////
        for(Item &i : items)
        {
            if(i.getActive())
            {
                i.update();
                if(checkCollision(i.getDestination(), player->getDestination()))
                {
                    i.setActive(false);
                    i.causeEffect(player);
                }
            }
        }
        ///// Update Items End/////
        checkBorders(*player);   //make sure player doesnt leave screen
    }
}
void PlayState::render(Game* game)
{

    SDL_SetRenderDrawColor(playRenderer, 255, 255, 255, 255);
    SDL_RenderClear(playRenderer);
    drawBackground(background);
    draw(*player,0);
    
    for(Entity &a: asteroids)
    {
        if(a.isActive())
        {
            draw(a,a.getRotationAngle());
        }
    }
    
    for(Item &i: items)
    {
        if(i.getActive())
        {
            draw(i,0);
        }
    }
    for(Projectile &p: playersBullets)
    {
        if(p.isActive())
        {
            draw(p,0);
        }
    }

    draw(hud,0);
    hud.drawText(playRenderer, "Hull integrity (%): ", hud.getDestination().x+20, hud.getDestination().y+10, 255, 255, 255);
    float hullIntegrity = ((float)player->getHps()/(float)player->getMaxHps()) * 100;
    hud.drawText(playRenderer, std::to_string(hullIntegrity).c_str(), hud.getDestination().x+160, hud.getDestination().y+10, 255, 255, 255);
    hud.drawText(playRenderer, "Rare elements (kg): ", hud.getDestination().x+20, hud.getDestination().y+25, 255, 255, 255);
    hud.drawText(playRenderer, std::to_string(player->getRareElements()).c_str(), hud.getDestination().x+160, hud.getDestination().y+25, 255, 255, 255);
    hud.drawText(playRenderer, "Metal Alloy (kg): ", hud.getDestination().x+20, hud.getDestination().y+40, 255, 255, 255);
    hud.drawText(playRenderer, std::to_string(player->getPreciousMetals()).c_str(), hud.getDestination().x+160, hud.getDestination().y+40, 255, 255, 255);
    
    for(int x = 0;x<=player->getShield()/10;x++)
    {
        hud.drawText(playRenderer, "Shield: ", hud.getDestination().x+20, hud.getDestination().y+55, 255, 255, 255);
        if(player->getShield()/10>5)
            hud.drawText(playRenderer,"|",hud.getDestination().x+160+(x*5),hud.getDestination().y+55,255,255,255);
        else if(player->getShield()/10<=5 && player->getShield()>0)
            hud.drawText(playRenderer,"|",hud.getDestination().x+160+(x*5),hud.getDestination().y+55,255,0,0);
        
    }
    hud.drawText(playRenderer, "Level: ", hud.getDestination().x+20, hud.getDestination().y+70, 255, 255, 255);
    hud.drawText(playRenderer, std::to_string(player->getLevel()).c_str(), hud.getDestination().x+160, hud.getDestination().y+70, 255, 255, 255);
    hud.drawText(playRenderer, "Score: ", hud.getDestination().x+20, hud.getDestination().y+85, 255, 255, 255);
    hud.drawText(playRenderer,std::to_string(player->getScore()).c_str(),hud.getDestination().x+160,hud.getDestination().y+85,255,255,255);
      hud.drawText(playRenderer, "ETA: ", hud.getDestination().x+20, hud.getDestination().y+100, 255, 255, 255);
      hud.drawText(playRenderer, std::to_string(levelTimer->getTimeLeft()).c_str(), hud.getDestination().x+160, hud.getDestination().y+100, 255, 255, 255);
    SDL_RenderPresent(playRenderer);

}
void PlayState::clean()
{
   
    levelTimer=nullptr;
    /* clear all vectors below */
    for(Projectile &p: playersBullets)
    {
        if(p.isActive())
        {
            p.setActive(false);
        }
    }
   
    for(Entity &a: asteroids)
    {
        if(a.isActive())
        {
            a.setActive(false);
        }
    }
    
    for(Item &i: items)
    {
        if(i.getActive())
        {
            i.setActive(false);
        }
    }
    playersBullets.clear();
    asteroids.clear();
    items.clear();
    if(levelTimer!=NULL)
    {
        delete levelTimer;
    }
    levelInfo.clear();
    texturePaths.clear();
    /* clear all vectors finished  */

    SDL_DestroyTexture(background.getTexture());
    SDL_DestroyTexture(player->getTexture());
    SDL_DestroyTexture(rareElement.getTexture());
    SDL_DestroyTexture(preciousMetal.getTexture());
    SDL_DestroyTexture(energyPulse.getTexture());
    SDL_DestroyTexture(playersBullet.getTexture());
    SDL_DestroyTexture(asteroid.getTexture());
    printf("PlayState Clean Successful\n");
}
