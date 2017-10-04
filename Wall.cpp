#include "Wall.h"


Wall::Wall(Ogre::SceneManager* mSceneMgr, int wallSize): wallMaterial("Examples/Rockwall") {
	 // Create plane and mesh
	this->mSceneMgr = mSceneMgr;
	this->wallSize = wallSize;

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
    Ogre::SceneNode *groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachGround(groundNode);

    Ogre::SceneNode *ceilingNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachCeiling(ceilingNode);

    Ogre::SceneNode *rightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachRight(rightNode);

    Ogre::SceneNode *leftNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachLeft(leftNode);

    Ogre::SceneNode *frontNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachFront(frontNode);

    Ogre::SceneNode *backNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    attachBack(backNode);
}

Ogre::Entity* Wall::getWallEntity(const char* materialName) {
	Ogre::Entity* wallEntity = mSceneMgr->createEntity("planeMesh");
    wallEntity->setCastShadows(false);
    wallEntity->setMaterialName(materialName);

    return wallEntity;
}

void Wall::attachFront(Ogre::SceneNode* frontNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	frontNode->attachObject(wallEntity);
    frontNode->pitch(Ogre::Radian(Ogre::Degree(-90)));
    frontNode->translate(Ogre::Vector3(0,0,wallSize/2));
}

void Wall::attachBack(Ogre::SceneNode* backNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	backNode->attachObject(wallEntity);
    backNode->pitch(Ogre::Radian(Ogre::Degree(90)));
    backNode->translate(Ogre::Vector3(0,0,-wallSize/2));
}

void Wall::attachLeft(Ogre::SceneNode* leftNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	leftNode->attachObject(wallEntity);
    leftNode->roll(Ogre::Radian(Ogre::Degree(90)));
    leftNode->yaw(Ogre::Radian(Ogre::Degree(90)));
    leftNode->translate(Ogre::Vector3(wallSize/2,0,0));
}

void Wall::attachRight(Ogre::SceneNode* rightNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	rightNode->attachObject(wallEntity);
    rightNode->roll(Ogre::Radian(Ogre::Degree(-90)));
    rightNode->yaw(Ogre::Radian(Ogre::Degree(90)));
    rightNode->translate(Ogre::Vector3(-wallSize/2,0,0));
}

void Wall::attachGround(Ogre::SceneNode* groundNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	groundNode->attachObject(wallEntity);
	groundNode->translate(Ogre::Vector3(0,-wallSize/2,0));
}

void Wall::attachCeiling(Ogre::SceneNode* ceilingNode) {
	Ogre::Entity* wallEntity = getWallEntity(wallMaterial);
	ceilingNode->attachObject(wallEntity);
	ceilingNode->roll(Ogre::Radian(Ogre::Degree(180)));
	ceilingNode->translate(Ogre::Vector3(0,wallSize/2,0));
}
