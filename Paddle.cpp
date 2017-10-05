#include <OgreEntity.h> 
#include <OgreSceneManager.h> 
#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* scnMgr) {
	 
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "paddleMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        wallSize, wallSize, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);

    Ogre::Entity* paddle = scnMgr->createEntity("paddleMesh");

    paddle->setMaterialName("Examples/SceneCubeMap2"); 
    paddle->setCastShadows(true); 

    rootNode = scnMgr->createSceneNode("Paddle"); 
    rootNode->attachObject(paddle); 

    //Need to change this part
    rootNode->scale(0.1,0.1,0.1); 
    rootNode->setPosition(Ogre::Vector3(0, 0, 0));
}

Paddle::move(Ogre:SceneEvent& evt){
	// Will move depending on user controls
	// The camera should move with the Paddle
}
