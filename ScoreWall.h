#ifndef __ScoreWall_h_
#define __ScoreWall_h_

#include <Ogre.h>
#include <vector>
#include "Goal.h"


class ScoreWall { 
protected:
	Ogre::SceneManager* scnMgr;
	int wallSize;
    double squareSize;
    std::vector<Goal> goals;
    Goal* activeGoal;
 	Physics* mPhysics;
 	int score;
    int scoreOther;

public: 
    ScoreWall(Ogre::SceneManager* scnMgr, Physics* mPhys, int wallSize);
    void createScoreWall();
    void allOff();
    void pickGoal(); 
    Goal* getActiveGoal() { return activeGoal; } 
    void increaseScore();
    void increaseScoreOther();
    int getScore();
    int getScoreOther();
    void resetScore();
    void resetScoreOther();
};

#endif
