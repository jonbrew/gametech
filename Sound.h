#ifndef __Sound_h_
#define __Sound_h_

#include <Ogre.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"


class Sound { 
protected:
	std::vector<Mix_Chunk*> sounds;
	Mix_Music* music;
	bool isOn;

public:
    int soundToPlay;
    static const int SOUND_NONE = -1;
	static const int SOUND_HIT = 0;
	static const int SOUND_BOUNCE = 1;
	static const int SOUND_SCORE = 2;
    static const int SOUND_WHIFF = 3;

    Sound();
    ~Sound();
    void toggle();
    void on();
    void off();
    void play(int i);
    bool getIsOn();
};

#endif
