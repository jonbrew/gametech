#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr, Physics* mPhys, int wallSize):
	wall(mSceneMgr, mPhys, wallSize),
	ball(mSceneMgr, mPhys),
	paddle(mSceneMgr, 30, 15)
{
	scoreWall = new ScoreWall(mSceneMgr, wallSize);
}

void Room::setup() {
	wall.createWalls();
	ball.createBall();
	scoreWall->createScoreWall();
}

ScoreWall* Room::getScoreWall() {
	return scoreWall;
}
