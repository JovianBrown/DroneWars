//
//  soundfx.cpp
//  DroneWars
//
//  Created by Jovian on 2021/12/11.
//  Copyright © 2021 mac. All rights reserved.
//

#include "soundfx.hpp"

Soundfx::Soundfx()
:volume(15),audio_rate(22050),audio_channels(2),audio_buffers(4096)
{
    
    Uint16 audio_format = AUDIO_S16SYS;
    
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) !=0)
    {
        std::cout<<"Unable to load audio device "<<std::endl;
    }
}
void Soundfx::addSound(const char* path)
{
    Mix_Chunk* tmpChunk = Mix_LoadWAV(path);
    if(tmpChunk !=nullptr)
    {
        soundFXLibrary.push_back(tmpChunk);
        std::cout<< (soundFXLibrary.size()-1) << " . sound loaded : " << path <<std::endl;
    }
    else
    {
        std::cout<<"Unable to load sound :" << path << std::endl;
    }
}

void Soundfx::playSound(const int id) const
{
    if(id > soundFXLibrary.size()-1)
    {
        std::cout<<"Sound doesnt exist"<<std::endl;
    }
    Mix_Volume(-1, volume);
    Mix_PlayChannel(-1, soundFXLibrary[id], 0);
}
Soundfx::~Soundfx()
{
    SDL_AudioQuit();
    std::cout<<"called SoundFx destructor"<<std::endl;
}


