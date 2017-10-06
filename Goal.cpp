#include "Goal.h"

Goal::Goal(Ogre::SceneManager* scnMgr, double goalSize, Ogre::Vector3 pos) { 
    goalEntity = scnMgr->createEntity("goalMesh");
    goalEntity->setMaterialName("Colors/Red");

    goalNode = scnMgr->getSceneNode("scoreWall")->createChildSceneNode();
    goalNode->attachObject(goalEntity);
    goalNode->setPosition(pos);

    this->off();
} 

void Goal::on() { 
    isActive = true;
    goalEntity->setMaterialName("Colors/Red");
}

void Goal::off() { 
    isActive = false;
    goalEntity->setMaterialName("Colors/Blue");
}
