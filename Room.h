#ifndef __Room_h_
#define __Room_h_

#include "Wall.h"
#include "Ball.h"

#endif


class Room {
public:
	Room(Ogre::SceneManager*);
	~Room(void);
	void setup(void);
private:
	Wall* wall;
	Ball* ball;
};
