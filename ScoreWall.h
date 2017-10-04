#include <Ogre.h>

class ScoreWall { 
    protected: 
        Ogre::SceneNode* rootNode; 
        int squareSize;
        std::vector<Goal> goals;
        Goal* activeGoal;

    public: 
        ScoreWall(Ogre::SceneManager* scnMgr, int wallSize); 
        ~ScoreWall(); 
        void pickGoal(); 
        Ogre::SceneNode* getNode() { return rootNode; } 
        Goal* getActiveGoal() { return activeGoal; } 
};