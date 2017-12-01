#ifndef __Goal_h_
#define __Goal_h_

#include <Ogre.h>
#include "Physics.h"

class Goal { 

protected: 
    Ogre::SceneNode* goalNode;
    Ogre::Entity* goalEntity;
    bool isActive;
    // Bullet fields
    Physics* mPhysics;
    btCollisionShape* btShape;
    btDefaultMotionState* btMotState;
	btScalar btMass; 
	btRigidBody* btBody; 
	btTransform btTrans; 
	btVector3 btInertia; 
    int health;
    void updateColor(int);

public: 
    Goal(Ogre::SceneManager* scnMgr, Physics* mPhys, double, Ogre::Vector3 pos); 
    //void on(int);
    void createBrick(int);
    void off();
    bool decHealth();
    bool isOn() { return isActive; }
    Ogre::SceneNode* getNode() { return goalNode; } 
};

#endif
