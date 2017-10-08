#ifndef __Room_h_
#define __Room_h_

#include <Ogre.h>
#include "Wall.h"
#include "Ball.h"
#include "ScoreWall.h"
#include "Paddle.h"


class Room {
public:
	Room(Ogre::SceneManager*, Physics* mPhys, int);
	void setup(void);
	ScoreWall* getScoreWall(void);
private:
	ScoreWall* scoreWall;
	Wall wall;
	Ball ball;
	Paddle paddle;
};

#endif
