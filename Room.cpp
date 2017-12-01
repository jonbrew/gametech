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
	brick = new Brick(mSceneMgr, mPhys);
	scoreWall = new ScoreWall(mSceneMgr, mPhys, wallSize);
	scoreWall->createScoreWall();
}

void Room::setupSingle() {
	ball->createBall(Ogre::Vector3(0,0,-60));
	ball->getRigidBody()->applyCentralImpulse(btVector3(0,10,75));
	paddle1 = new Paddle(mSceneMgr, mPhys, 30, 15, Ogre::Vector3(0,0,-75), -90);
	brick->createBrick(Ogre::Vector3(10, 10, 10), 2);
}

void Room::setupMulti() {
	ball->createBall(Ogre::Vector3(0,0,0));
	ball->getRigidBody()->applyCentralImpulse(btVector3(0,10,75));
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

Brick* Room::getBrick(){
	return brick;
}

void Room::reset() {
	// Reset ball
	ball->reset();
	// Reset paddle
	paddle1->reset();
}

void Room::resetMultiplayer(int roundNum) {
	// Reset ball
	ball->resetMultiplayer(roundNum);
	// Reset paddles
	paddle1->reset();
	paddle2->reset();
}
