#ifndef __Brick_h_
#define __Brick_h_

#include <Ogre.h>
#include "Physics.h"

class Brick {
protected:
	int brick_level;
	Ogre::Entity* brick;
	char* brick_material;
	Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* rootNode;
    Physics* mPhysics;
	btCollisionShape* btShape;
	btRigidBody* btBody; 
	btDefaultMotionState *btMotionState;
	btScalar btMass; ; 
	btTransform btTrans; 
	btVector3 btInertia; 

public:
	Brick(Ogre::SceneManager*, Physics*);
	virtual ~Brick(void);
	void createBrick(Ogre::Vector3, int);
	bool hitBrick();
	void updateColor(int);
    Ogre::SceneNode* getNode(void) { return rootNode; }
    btRigidBody* getRigidBody(void) { return btBody; }

};

#endif