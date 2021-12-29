//
//  object.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "object.hpp"

void Object::setSource(int x, int y, int width, int height)
{
    this->source.x=x;
    this->source.y=y;
    this->source.w=width;
    this->source.h=height;
}

void Object::setDestination(int x, int y, int width, int height)
{
    this->destination.x=x;
    this->destination.y=y;
    this->destination.w=width;
    this->destination.h=height;
}

void Object::setImage(std::string filename, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
    {
        std::cout<<"Unable to load texture: "<<filename<<std::endl;
    }
    else
    {
        std::cout<<"Loaded texture : "<<filename<<std::endl;
    }
    SDL_FreeSurface(surface);
}


void Object::draw(Object &object,SDL_Renderer *renderer)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(renderer,object.getTexture(),&source,&destination,0,NULL,SDL_FLIP_NONE);
}
