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
	static const int SOUND_BOUNCE = 1;
	static const int SOUND_SCORE = 2;

    Sound();
    ~Sound();
    void toggle();
    void on();
    void off();
    void play(int i);
    bool getIsOn();
};

#endif
