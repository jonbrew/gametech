#ifndef __Room_h_
#define __Room_h_

#include <Ogre.h>
#include "Wall.h"
#include "Ball.h"
#include "ScoreWall.h"
#include "Paddle.h"
#include "Goal.h"

class Room {
public:
	Room(Ogre::SceneManager*, Physics*, int);
	void setup(void);
	ScoreWall* getScoreWall(void);
	Paddle* getPaddle(void);
	Ball* getBall(void);
	void reset(void);
private:
	Physics* mPhys;
	Ogre::SceneManager* mSceneMgr;
	ScoreWall* scoreWall;
	Wall wall;
	Ball* ball;
	Paddle* paddle;
};

#endif
