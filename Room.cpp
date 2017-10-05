#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr) {
	wall = new Wall(mSceneMgr, 200);
	ball = new Ball(mSceneMgr);
}

Room::~Room() {
	delete wall;
	delete ball;
}

void Room::setup(void) {
	wall->Wall::createWalls();
	ball->Ball::createBall();
}
