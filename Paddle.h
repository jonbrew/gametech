#ifndef __Paddle_h_
#define __Paddle_h_

#include <Ogre.h>


class Paddle {
private:
	Ogre::SceneNode* paddleNode;

public:
	Paddle(Ogre::SceneManager*, int, int);
};

#endif
