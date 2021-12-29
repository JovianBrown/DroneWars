//
//  soundfx.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//


#ifndef soundfx_hpp
#define soundfx_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2_mixer/SDL_mixer.h>
#include <vector>


class Soundfx
{
public:
    Soundfx();
    ~Soundfx();
    void addSound(const char* path);
    void playSound(const int id) const;
    void setVolume(int v)
    {
        volume = v;
    }
private:
    std::vector <Mix_Chunk*> soundFXLibrary;
    int volume;
    int audio_rate;
    int audio_channels;
    int audio_buffers;

};
#endif /* soundfx_hpp */
