#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr, Physics* mPhys, int wallSize):
	wall(mSceneMgr, mPhys, wallSize)
{
	this->mPhys = mPhys;
	this->mSceneMgr = mSceneMgr;
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
	ball->reset();
	// Reset paddle
	paddle->reset();
	// Reset wall
}
