#include "Sound.h"

Sound::Sound() { 
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    music = Mix_LoadMUS("Sounds/music.wav");
    if(!music)
        std::cout << "FAILED TO LOAD\n";
    sounds.push_back(Mix_LoadWAV("Sounds/hit.wav"));
    sounds.push_back(Mix_LoadWAV("Sounds/bounce.wav"));
    sounds.push_back(Mix_LoadWAV("Sounds/score.wav"));
    Mix_PlayMusic(music,-1);
    isOn = true;
} 

Sound::~Sound() {
    Mix_FreeMusic(music);
    for(int i = 0; i < sounds.size(); ++i) {
        Mix_FreeChunk(sounds[i]);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void Sound::toggle() {
    if(isOn) {
        off();
    }
    else {
        on();
    }
}

void Sound::on() {
    Mix_ResumeMusic();
    isOn = true;
}

void Sound::off() {
    Mix_PauseMusic();
    isOn = false;
}

void Sound::play(int i) {
    if(isOn)
        Mix_PlayChannel(-1,sounds[i],0);
}

bool Sound::getIsOn() {
    return isOn;
}