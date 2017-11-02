#include "Goal.h"

Goal::Goal(Ogre::SceneManager* scnMgr, Physics* mPhys, double goalSize, Ogre::Vector3 pos) { 
    goalEntity = scnMgr->createEntity("goalMesh");
    goalEntity->setMaterialName("Colors/Blue");

    goalNode = scnMgr->getSceneNode("scoreWall")->createChildSceneNode();
    goalNode->attachObject(goalEntity);
    goalNode->setPosition(pos);
    mPhysics = mPhys;
    //create the new physics shape
    btShape = new btBoxShape(btVector3(goalSize/2,0.f,goalSize/2));    
    mPhysics->getCollisionShapes().push_back(btShape);
    btTransform goalTransform;
    goalTransform.setIdentity();
    goalTransform.setRotation(btQuaternion(btRadians(0),btRadians(90),btRadians(0)));
    goalTransform.setOrigin(btVector3(pos.x,pos.z,100));
    btMass = 0.; //the mass is 0, because the ground is immovable (static)
    btInertia = btVector3(0, 0, 0);
    btMotState = new btDefaultMotionState(goalTransform);
    btShape->calculateLocalInertia(btMass, btInertia);
    btRigidBody::btRigidBodyConstructionInfo goalRBInfo(btMass, btMotState, btShape, btInertia);
    btBody = new btRigidBody(goalRBInfo);
    btBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    btBody->setUserIndex(Physics::TYPE_GOAL_OFF);
    btBody->setUserPointer(this);
    btBody->setRestitution(1);
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);
} 

void Goal::on() { 
    isActive = true;
    btBody->setUserIndex(Physics::TYPE_GOAL_ON);
    goalEntity->setMaterialName("Colors/RadioactiveGreen");
}

void Goal::off() { 
    isActive = false;
    btBody->setUserIndex(Physics::TYPE_GOAL_OFF);
    goalEntity->setMaterialName("Colors/Red");
}
