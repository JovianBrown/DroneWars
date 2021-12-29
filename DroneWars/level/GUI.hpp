//
//  GUI.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef GUI_hpp
#define GUI_hpp

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "object.hpp"
class GUI : public Object
{
  
    public:
        void initGUI(int &windowWidth,int &windowHeight);
        void drawText(SDL_Renderer* renderer, const char* msg, int x, int y, int r, int g, int b);
        void clean();
        
    private:
        SDL_Color textColor;
        SDL_Surface *message;
        SDL_Surface* surf;
        SDL_Rect textRect;
        TTF_Font *font;
        SDL_Texture *text;
        SDL_Renderer* guiRenderer;
};

#endif /* GUI_hpp */
