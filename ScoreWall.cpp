#include "ScoreWall.h"


ScoreWall::ScoreWall(Ogre::SceneManager* scnMgr, int wallSize) { 
    this->scnMgr = scnMgr;
    this->wallSize = wallSize;
    squareSize = ((double) wallSize) / 3;

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "goalMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        squareSize, squareSize, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);

    Ogre::MeshManager::getSingleton().createPlane(
        "scoreMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        wallSize, wallSize, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);
}

void ScoreWall::createScoreWall() {
    Ogre::Entity* scoreWallEntity = scnMgr->createEntity("scoreMesh");
    scoreWallEntity->setVisible(false);
    scoreWallEntity->setMaterialName("Colors/Red");

    Ogre::SceneNode* scoreWallNode = scnMgr->getRootSceneNode()->createChildSceneNode("scoreWall");
    scoreWallNode->attachObject(scoreWallEntity);
    scoreWallNode->pitch(Ogre::Radian(Ogre::Degree(-90)));
    scoreWallNode->translate(Ogre::Vector3(0,0,wallSize/2));

    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(0,0,0)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(squareSize,0,0)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(-squareSize,0,0)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(0,0,squareSize)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(squareSize,0,squareSize)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(-squareSize,0,squareSize)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(0,0,-squareSize)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(squareSize,0,-squareSize)));
    goals.push_back(Goal(scnMgr, squareSize, Ogre::Vector3(-squareSize,0,-squareSize)));
}

void ScoreWall::pickGoal() { 
    int i = rand()%(goals.size()-0 + 1) + 0;
    if(activeGoal)
        activeGoal->off();
    activeGoal = &(goals[i]);
    activeGoal->on();
}
