#ifndef __Room_h_
#define __Room_h_

#include "Wall.h"

#endif


class Room {
public:
	Room(Ogre::SceneManager*);
	void setup(void);
private:
	Wall* wall;
};
