//
//  menugui.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//
// could modify this class and hud to share inherit a basic class that implements text
//maybe inherit twice, one from object : GUI : dockMenu etc
#ifndef menugui_hpp
#define menugui_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "GUI.hpp"

class MenuGUI : public GUI
{
public:
    MenuGUI()
    :x(0),y(0),width(500),height(175)
    {
    }
    void initMenuGUI(SDL_Renderer* renderer,int &windowWidth,int &windowHeight);
    void update();
    void setSelected(bool b)
    {
        selected = b;
    }
    bool isSelected()
    {
        return selected;
    }
  
    void clean();
private:


    int x,y,width,height;
    int windowWidth,windowHeight;
    int menuWidth,menuHeight;
    int selection;
    int totalSelections;
    bool selected;
};
#endif /* menugui_hpp */
