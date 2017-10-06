#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr, int wallSize):
	wall(mSceneMgr, wallSize),
	ball(mSceneMgr),
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
