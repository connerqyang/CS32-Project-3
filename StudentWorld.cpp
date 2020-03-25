#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_socrates = nullptr;
    m_numActors = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    m_numActors = max(180 - 20 * getLevel(), 20);    // Number of Dirt objects, based on the level
    
        // Add all Dirt objects
    for (int i = 0; i < m_numActors; i++)
    {
        double yFromOrigin = randInt(-120, 120);    // 120 is max distance from center
            // Pythagoream Thrm
        int maxXDistance = sqrt(120 * 120 - yFromOrigin * yFromOrigin);
        int xFromOrigin = randInt(-maxXDistance, maxXDistance);
        
        double x = VIEW_WIDTH / 2 + xFromOrigin;
        double y = VIEW_HEIGHT / 2 + yFromOrigin;
        Actor* a =  new Dirt(this, x, y);
        m_actors.push_back(a);
    }
    
    m_socrates = new Socrates(this);    // Allocate Socrates
    
    return GWSTATUS_CONTINUE_GAME;
}

    // Implement the move() method in your StudentWorld class. During each tick, it must ask Socrates and other actors (just dirt piles for now) to do something. Your move() method need not check to see if Socrates has died or not; you may assume for Part #1 that Socrates cannot die. Your move() method does not have to deal with any actors other than Socrates and the dirt piles.
int StudentWorld::move()
{
    m_socrates->doSomething();  // Player moves first
    
        // Prompt all Actors to move
    for (int i = 0; i < m_numActors; i++)
    {
        if (m_actors[i]->isAlive())
            m_actors[i]->doSomething();
    }
    
        // Delete for dead Actors
    vector<Actor*>::iterator a, b, itr;
    
    a = m_actors.begin();
    b = m_actors.end();
    
    while (itr != b)
    {
        itr = find_if(a, b, isDead);
        if (itr != b)
        {
                // Must delete before erasing, as erasing in a vector shuffles memory
            delete *itr;
            m_actors.erase(itr);
            a = m_actors.begin();
            b = m_actors.end();
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

    // Free all dynamically-allocated memory
void StudentWorld::cleanUp()
{
        // Delete all actors in the vector container
    for (int i = 0; i < m_numActors; i++)
        delete m_actors[i];
    
    delete m_socrates;  // Delete Socrates
}

bool isDead(Actor* a)
{
    if (a->isAlive())
        return false;
    else
        return true;
}
