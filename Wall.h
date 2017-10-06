#ifndef __Wall_h_
#define __Wall_h_

#include <Ogre.h>


class Wall {
public:
	Wall(Ogre::SceneManager*, int);
	void createWalls(void);
private:
	Ogre::SceneManager* mSceneMgr;
	int wallSize;
	const char* wallMaterial;

	Ogre::Entity* getWallEntity(const char*);
	void attachFront(Ogre::SceneNode*);
	void attachBack(Ogre::SceneNode*);
	void attachLeft(Ogre::SceneNode*);
	void attachRight(Ogre::SceneNode*);
	void attachGround(Ogre::SceneNode*);
	void attachCeiling(Ogre::SceneNode*);
};

#endif
