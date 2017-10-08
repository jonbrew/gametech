#ifndef __Sound_h_
#define __Sound_h_

#include <Ogre.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"


class Sound { 
protected:
	std::vector<Mix_Chunk*> sounds;
	bool isOn;

public:
	static const int SOUND_HIT = 0;

    Sound();
    ~Sound();
    void on();
    void off();
    void play(int i);
};

#endif
