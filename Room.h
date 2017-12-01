#ifndef __Room_h_
#define __Room_h_

#include <Ogre.h>
#include "Wall.h"
#include "Ball.h"
#include "ScoreWall.h"
#include "Paddle.h"
#include "Goal.h"
#include "Brick.h"

class Room {
public:
	Room(Ogre::SceneManager*, Physics*, int);
	void setupSingle(void);
	void setupMulti(void);
	ScoreWall* getScoreWall(void);
	Paddle* getPaddle1(void);
	Paddle* getPaddle2(void);
	Ball* getBall(void);
	void reset(void);
	void resetMultiplayer(int roundNum);
	void generateBricks(int roundNum);

private:
	Physics* mPhys;
	Ogre::SceneManager* mSceneMgr;
	ScoreWall* scoreWall;
	Wall wall;
	Ball* ball;
	Paddle* paddle1;
	Paddle* paddle2;
	std::list<Brick*> bricks;
	void setProbability(int,int&,int&,int&,int&);
};

#endif
