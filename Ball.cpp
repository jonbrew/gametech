#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr, Physics* mPhys) {
    sceneMgr = scnMgr;
    mPhysics = mPhys;
    bRadius = 10.0f; 
    bDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f); 
    bDirection.normalise(); 
    bSpeed = 250.0f; 
}

void Ball::createBall() {
    Ogre::Entity* ball = sceneMgr->createEntity("Sphere", "sphere.mesh"); 
    ball->setCastShadows(true);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Ball"); 
    rootNode->attachObject(ball);
    rootNode->scale(0.07,0.07,0.07); 
    rootNode->setPosition(Ogre::Vector3(0, 0, -65));
    //create the new physics shape
    btShape = new btSphereShape(btScalar(bRadius));
    mPhysics->getCollisionShapes().push_back(btShape);
    //set the initial position and transform
    btTrans.setRotation(btQuaternion(1.0f, 1.0f, 1.0f, 0));
    //set the mass of the object. a mass of "0" means that it is an immovable object
    btMass = 0.75f;
    btInertia = btVector3(0,0,0);
    btTrans.setOrigin(btVector3(0,0,-65));
    btShape->calculateLocalInertia(btMass, btInertia);
    //construct the body and add it to the dynamics world
    btMotionState = new btDefaultMotionState(btTrans);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(btMass, btMotionState, btShape, btInertia);
    btBody = new btRigidBody(rbInfo);
    btBody->setRestitution(0.85);
    btBody->setFriction(0);
    btBody->setRollingFriction(0.5);
    btBody->setUserPointer(rootNode);
    btBody->setUserIndex(Physics::TYPE_BALL);
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);
    btBody->applyCentralImpulse(btVector3(0,10,-50));
}

void Ball::resetBall() {
    rootNode->setPosition(Ogre::Vector3(0, 0, -65));
    btTrans.setOrigin(btVector3(0,0,-65));
}
