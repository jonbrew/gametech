#include "Paddle.h"


Paddle::Paddle(Ogre::SceneManager* scnMgr, int paddleWidth, int paddleHeight) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "paddleMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        paddleWidth, paddleHeight, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);

    Ogre::Entity* paddleEntity = scnMgr->createEntity("paddleMesh");
    paddleEntity->setMaterialName("Colors/RadioactiveGreen");

    paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode("Paddle");
    paddleNode->attachObject(paddleEntity);
    paddleNode->pitch(Ogre::Radian(Ogre::Degree(-90)));
    paddleNode->translate(Ogre::Vector3(0,0,-50));

    
}
