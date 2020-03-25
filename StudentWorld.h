#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>

class Actor;
class Socrates;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
  public:
        // Constructor and Destructor
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    
        // Re-defined functions
    virtual int init();
    virtual int move();
    virtual void cleanUp();

  private:
    std::vector<Actor*> m_actors;   // Vector holding all actors in the game
    Socrates* m_socrates;
    int m_numActors;    // The number of actors, excluding Socrates
};

bool isDead(Actor* a);

#endif // STUDENTWORLD_H_
