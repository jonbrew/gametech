#include "Wall.h"


Wall::Wall(Ogre::SceneManager* mSceneMgr, Physics* mPhys, int wallSize): wallMaterial("Colors/Blue") {
	 // Create plane and mesh
	this->mSceneMgr = mSceneMgr;
	this->wallSize = wallSize;
    mPhysics = mPhys;
    wallShape = new btBoxShape(btVector3(100.f,0.f,100.f));
    mPhysics->getCollisionShapes().push_back(wallShape);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "planeMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        wallSize, wallSize, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);
}

void Wall::createWalls() {
	// Create SceneNodes
    Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachGround(groundNode);

    Ogre::SceneNode* ceilingNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachCeiling(ceilingNode);

    Ogre::SceneNode* rightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachRight(rightNode);

    Ogre::SceneNode* leftNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachLeft(leftNode);

    Ogre::SceneNode* backNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachBack(backNode);
}

Ogre::Entity* Wall::getWallEntity(const char* materialName) {
	Ogre::Entity* wallEntity = mSceneMgr->createEntity("planeMesh");
    wallEntity->setCastShadows(false);
    wallEntity->setMaterialName(materialName);

    return wallEntity;
}

void Wall::attachBack(Ogre::SceneNode* backNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	backNode->attachObject(wallEntity);
    backNode->pitch(Ogre::Radian(Ogre::Degree(90)));
    backNode->translate(Ogre::Vector3(0,0,-wallSize/2));
    btTransform backTransform;
    backTransform.setIdentity();
    backTransform.setRotation(btQuaternion(btRadians(0),btRadians(90),btRadians(0)));
    backTransform.setOrigin(btVector3(0,0,-wallSize/2));
    btScalar backMass(0.); //the mass is 0, because the ground is immovable (static)
    btVector3 localBackInertia(0, 0, 0);
    btDefaultMotionState *backMotionState = new btDefaultMotionState(backTransform);
    wallShape->calculateLocalInertia(backMass, localBackInertia);
    btRigidBody::btRigidBodyConstructionInfo backRBInfo(backMass, backMotionState, wallShape, localBackInertia);
    btRigidBody *backBody = new btRigidBody(backRBInfo);
    backBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    backBody->setUserIndex(Physics::TYPE_WALL);
    backBody->setRestitution(1);
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(backBody);
}

void Wall::attachLeft(Ogre::SceneNode* leftNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	leftNode->attachObject(wallEntity);
    leftNode->roll(Ogre::Radian(Ogre::Degree(90)));
    leftNode->yaw(Ogre::Radian(Ogre::Degree(90)));
    leftNode->translate(Ogre::Vector3(wallSize/2,0,0));
    btTransform leftTransform;
    leftTransform.setIdentity();
    leftTransform.setRotation(btQuaternion(btRadians(0),btRadians(0),btRadians(90)));
    leftTransform.setOrigin(btVector3(wallSize/2,0,0));
    btScalar leftMass(0.); //the mass is 0, because the ground is immovable (static)
    btVector3 localleftInertia(0, 0, 0);
    btDefaultMotionState *leftMotionState = new btDefaultMotionState(leftTransform);
    wallShape->calculateLocalInertia(leftMass, localleftInertia);
    btRigidBody::btRigidBodyConstructionInfo leftRBInfo(leftMass, leftMotionState, wallShape, localleftInertia);
    btRigidBody *leftBody = new btRigidBody(leftRBInfo);
    leftBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    leftBody->setUserIndex(Physics::TYPE_WALL);
    leftBody->setRestitution(1);
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(leftBody);
}

void Wall::attachRight(Ogre::SceneNode* rightNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	rightNode->attachObject(wallEntity);
    rightNode->roll(Ogre::Radian(Ogre::Degree(-90)));
    rightNode->yaw(Ogre::Radian(Ogre::Degree(90)));
    rightNode->translate(Ogre::Vector3(-wallSize/2,0,0));
    btTransform rightTransform;
    rightTransform.setIdentity();
    rightTransform.setRotation(btQuaternion(btRadians(0),btRadians(0),btRadians(-90)));
    rightTransform.setOrigin(btVector3(-wallSize/2,0,0));
    btScalar rightMass(0.); //the mass is 0, because the ground is immovable (static)
    btVector3 localrightInertia(0, 0, 0);
    btDefaultMotionState *rightMotionState = new btDefaultMotionState(rightTransform);
    wallShape->calculateLocalInertia(rightMass, localrightInertia);
    btRigidBody::btRigidBodyConstructionInfo rightRBInfo(rightMass, rightMotionState, wallShape, localrightInertia);
    btRigidBody *rightBody = new btRigidBody(rightRBInfo);
    rightBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    rightBody->setUserIndex(Physics::TYPE_WALL);
    rightBody->setRestitution(1);
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(rightBody);
}

void Wall::attachGround(Ogre::SceneNode* groundNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	groundNode->attachObject(wallEntity);
	groundNode->translate(Ogre::Vector3(0,-wallSize/2,0));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -wallSize/2, 0));
    btScalar groundMass(0.); //the mass is 0, because the ground is immovable (static)
    btVector3 localGroundInertia(0, 0, 0);
    btDefaultMotionState *groundMotionState = new btDefaultMotionState(groundTransform);
    wallShape->calculateLocalInertia(groundMass, localGroundInertia);
    btRigidBody::btRigidBodyConstructionInfo groundRBInfo(groundMass, groundMotionState, wallShape, localGroundInertia);
    btRigidBody *groundBody = new btRigidBody(groundRBInfo);
    groundBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    groundBody->setUserIndex(Physics::TYPE_WALL);
    groundBody->setRestitution(1);
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(groundBody);
}

void Wall::attachCeiling(Ogre::SceneNode* ceilingNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	ceilingNode->attachObject(wallEntity);
	ceilingNode->roll(Ogre::Radian(Ogre::Degree(180)));
	ceilingNode->translate(Ogre::Vector3(0,wallSize/2,0));
    btTransform ceilingTransform;
    ceilingTransform.setIdentity();
    ceilingTransform.setRotation(btQuaternion(btRadians(0),btRadians(0),btRadians(180)));
    ceilingTransform.setOrigin(btVector3(0,wallSize/2,0));
    btScalar ceilingMass(0.); //the mass is 0, because the ground is immovable (static)
    btVector3 localceilingInertia(0, 0, 0);
    btDefaultMotionState *ceilingMotionState = new btDefaultMotionState(ceilingTransform);
    wallShape->calculateLocalInertia(ceilingMass, localceilingInertia);
    btRigidBody::btRigidBodyConstructionInfo ceilingRBInfo(ceilingMass, ceilingMotionState, wallShape, localceilingInertia);
    btRigidBody *ceilingBody = new btRigidBody(ceilingRBInfo);
    ceilingBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
    ceilingBody->setUserIndex(Physics::TYPE_WALL);
    ceilingBody->setRestitution(1);
    //add the body to the dynamics world
    mPhysics->getDynamicsWorld()->addRigidBody(ceilingBody);
}
