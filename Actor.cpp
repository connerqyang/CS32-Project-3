#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>

#define PI 3.1415926535

// IMPLEMENTATION FOR Actor

    // Constructor for Actor
Actor::Actor(int imageId, StudentWorld* world, double x, double y, Direction startDirection, int depth)
    :GraphObject(imageId, x, y, startDirection, depth)
{
    m_world = world;
    m_isAlive = true;
}

bool Actor::isAlive() const
{
    return m_isAlive;
}

void Actor::kill()
{
    m_isAlive = false;
}

StudentWorld* Actor::getWorldPtr() const
{
    return m_world;
}


// IMPLEMENTATION FOR AliveActor

    // Constructor for AliveActor
AliveActor::AliveActor(int imageId, StudentWorld* world, double x, double y, Direction startDirection, int depth, int hitPoints)
    :Actor(imageId, world, x, y, startDirection, depth)
{
    m_hitPoints = hitPoints;
}

    // Accessor and Mutator for m_hitPoints
int AliveActor::getHitPoints() const
{
    return m_hitPoints;
}

void AliveActor::addToHitPoints(int change)
{
    m_hitPoints += change;
}


// IMPLEMENTATION FOR Socrates

    // Constructor for Socrates
Socrates::Socrates(StudentWorld* world)
    :AliveActor(IID_PLAYER, world, 0, VIEW_HEIGHT / 2, right, 0, 100)
{
    m_positionalAngle = 180;
    m_numSprayCharges = 20;
    m_numFlamethrowerCharges = 5;
}

    // It must have a limited version of a doSomething() method that lets the user pick a direction by hitting a directional key. If the player hits a directional key during the current tick, your code must update Socrates’s location appropriately, moving him clockwise or counterclockwise around the Petri dish. All this doSomething() method has to do is properly adjust Socrates’s (x, y) coordinates using the GraphObject class’s moveTo() method, and our graphics system will automatically animate its movement it around the Petri dish!
void Socrates::doSomething()
{
        // If Socrates is not alive, return immediately
    if (!isAlive())
        return;
    
    int counterClockWise = 5;
    int clockWise = -5;
    int ch;
    if (getWorldPtr()->getKey(ch))
    {
        switch (ch) {
            case KEY_PRESS_LEFT:
                changePositionalAngle(counterClockWise);
                move();
                setDirection(getPositionalAngle() + 180);
                break;
            case KEY_PRESS_RIGHT:
                changePositionalAngle(clockWise);
                move();
                setDirection(getPositionalAngle() + 180);
                break;
            default:
                break;
        }
    }
    else if (m_numSprayCharges < 20)  // The player did not press a key
    {
        m_numSprayCharges++;    // Socrates gets an extra spray!
    }
}

int Socrates::getPositionalAngle() const
{
    return m_positionalAngle;
}

void Socrates::changePositionalAngle(int degrees)
{
    m_positionalAngle += degrees;
}

void Socrates::move()
{
    double newX = (VIEW_WIDTH / 2) +
        (VIEW_RADIUS * cos(PI/180 * getPositionalAngle()));
    
    double newY = (VIEW_HEIGHT / 2) +
        (VIEW_RADIUS * sin(PI/180 * getPositionalAngle()));
    
    moveTo(newX, newY);
}


// IMPLEMENTATION OF Dirt

    // Constructor for Dirt
Dirt::Dirt(StudentWorld* world, double x, double y)
    :Actor(IID_DIRT, world, x, y, right, 1)
{}

    // "C'mon - it's dirt. What could it do?"
void Dirt::doSomething()
{
    return;
}
