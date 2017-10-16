#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr, Physics* mPhys, int wallSize):
	wall(mSceneMgr, mPhys, wallSize)
{
	ball = new Ball(mSceneMgr, mPhys);
	paddle = new Paddle(mSceneMgr, mPhys, 30, 15);
	scoreWall = new ScoreWall(mSceneMgr, mPhys, wallSize);
}

void Room::setup() {
	wall.createWalls();
	ball->createBall();
	scoreWall->createScoreWall();
}

ScoreWall* Room::getScoreWall() {
	return scoreWall;
}

Paddle* Room::getPaddle() {
	return paddle;
}

Ball* Room::getBall() {
	return ball;
}

void Room::reset() {
	// Reset ball
	// Reset paddle
	// Reset wall
}
