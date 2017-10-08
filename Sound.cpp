#include "Sound.h"

Sound::Sound() { 
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    sounds.push_back(Mix_LoadWAV("Sounds/hit.wav"));
    isOn = true;
} 

Sound::~Sound() {
    for(int i = 0; i < sounds.size(); ++i) {
        Mix_FreeChunk(sounds[i]);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void Sound::on() {
    isOn = true;
}

void Sound::off() {
    isOn = false;
}

void Sound::play(int i) {
    if(isOn)
        Mix_PlayChannel(-1,sounds[i],0);
}