#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr, Physics* mPhys) {
    sceneMgr = scnMgr;
    mPhysics = mPhys;
    bRadius = 10.0f; 
    bDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f); 
    bDirection.normalise(); 
    bSpeed = 250.0f; 
}

void Ball::createBall(Ogre::Vector3 startPos) {
    Ogre::Entity* ball = sceneMgr->createEntity("Sphere", "sphere.mesh"); 
    ball->setCastShadows(true);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Ball"); 
    rootNode->attachObject(ball);
    rootNode->scale(0.07,0.07,0.07); 
    rootNode->setPosition(startPos);
    //create the new physics shape
    btShape = new btSphereShape(btScalar(7));
    mPhysics->getCollisionShapes().push_back(btShape);
    //set the initial position and transform
    btTrans.setRotation(btQuaternion(1.0f, 1.0f, 1.0f, 0));
    //set the mass of the object. a mass of "0" means that it is an immovable object
    btMass = 0.75f;
    btInertia = btVector3(0,0,0);
    btTrans.setOrigin(btVector3(startPos.x,startPos.y,startPos.z));
    btShape->calculateLocalInertia(btMass, btInertia);
    //construct the body and add it to the dynamics world
    btMotionState = new btDefaultMotionState(btTrans);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(btMass, btMotionState, btShape, btInertia);
    btBody = new btRigidBody(rbInfo);
    btBody->setRestitution(1.0);
    btBody->setFriction(0.0);
    btBody->setUserPointer(rootNode);
    btBody->setUserIndex(Physics::TYPE_BALL);
    mPhysics->getDynamicsWorld()->addRigidBody(btBody);
}

void Ball::reset() {
    rootNode->setPosition(Ogre::Vector3(0, 0, -60));
    btBody->setCenterOfMassTransform(btTransform(btQuaternion(1.0f, 1.0f, 1.0f, 0),btVector3(0,0,-60)));
    
    btBody->clearForces();
    btBody->setLinearVelocity(btVector3(0, 0, 0));
    btBody->setAngularVelocity(btVector3(0, 0, 0));
    btBody->applyCentralImpulse(btVector3(0,10,75));
}

void Ball::resetMultiplayer(int roundNum) {
    rootNode->setPosition(Ogre::Vector3(0, 0, 0));

    btBody->clearForces();
    btBody->setLinearVelocity(btVector3(0, 0, 0));
    btBody->setAngularVelocity(btVector3(0, 0, 0));

    btBody->setCenterOfMassTransform(btTransform(btQuaternion(1.0f, 1.0f, 1.0f, 0)));
    if(roundNum%2 == 0) // Alternate starting impulse each round
        btBody->applyCentralImpulse(btVector3(0,10,75));
    else
        btBody->applyCentralImpulse(btVector3(0,10,-75));

}

void Ball::printPos() {
    Ogre::Vector3 pos = rootNode->getPosition();
    std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";
}
