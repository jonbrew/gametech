#include <Ogre.h>
#include "Goal.h"

class ScoreWall { 
    protected:  
        int squareSize;
        std::vector<Goal> goals;
        Goal* activeGoal;

    public: 
        ScoreWall(Ogre::SceneManager* scnMgr, int wallSize); 
        ~ScoreWall(); 
        void pickGoal(); 
        Goal* getActiveGoal() { return activeGoal; } 
};