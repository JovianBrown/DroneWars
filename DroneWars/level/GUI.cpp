//
//  GUI.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "GUI.hpp"


void GUI::initGUI( int &windowWidth, int &windowHeight)
{
   
    TTF_Init();
    font = TTF_OpenFont("res/Georgia.ttf",12);
    if(font==NULL)
    {
        std::cout<<"unable to load font"<<std::endl;
    }
}


void GUI::drawText(SDL_Renderer* renderer, const char *msg, int x, int y, int r, int g, int b)
{
    SDL_Color color;
    color.r=r;
    color.g=g;
    color.b=b;
    color.a=255;
    SDL_Rect rect;
    surf=TTF_RenderText_Solid(font,msg,color);
    text=SDL_CreateTextureFromSurface(renderer,surf);
    rect.x=x;
    rect.y=y;
    rect.w=surf->w;
    rect.h=surf->h;
    SDL_FreeSurface(surf);
    SDL_RenderCopy(renderer,text,NULL,&rect);
    SDL_DestroyTexture(text);
}

void GUI::clean()
{
    std::cout<<"GUI cleaned successfully"<<std::endl;
    delete message;
    TTF_Quit();
}
