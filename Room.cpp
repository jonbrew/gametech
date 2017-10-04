#include "Room.h"


Room::Room(Ogre::SceneManager* mSceneMgr) {
	wall = new Wall(mSceneMgr, 200);
}

void Room::setup(void) {
	wall->Wall::createWalls();
}
