#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr, Physics* mPhys, int wallSize):
	wall(mSceneMgr, mPhys, wallSize)
{
	this->mPhys = mPhys;
	this->mSceneMgr = mSceneMgr;
	wall.createWalls();
	ball = new Ball(mSceneMgr, mPhys);
	paddle1 = NULL;
	paddle2 = NULL;
	scoreWall = new ScoreWall(mSceneMgr, mPhys, wallSize);
	scoreWall->createScoreWall();
}

void Room::setupSingle() {
	ball->createBall();
	paddle1 = new Paddle(mSceneMgr, mPhys, 30, 15, Ogre::Vector3(0,0,-75), -90);
}

void Room::setupMulti() {
	ball->createBall();
	paddle1 = new Paddle(mSceneMgr, mPhys, 30, 15, Ogre::Vector3(0,0,-75), -90);
	paddle2 = new Paddle(mSceneMgr, mPhys, 30, 15, Ogre::Vector3(0,0,75), 90);
}

ScoreWall* Room::getScoreWall() {
	return scoreWall;
}

Paddle* Room::getPaddle1() {
	return paddle1;
}

Paddle* Room::getPaddle2() {
	return paddle2;
}

Ball* Room::getBall() {
	return ball;
}

void Room::reset() {
	// Reset ball
	ball->reset();
	// Reset paddles
	paddle1->reset();
	if(paddle2 != NULL)
		paddle2->reset();
}
