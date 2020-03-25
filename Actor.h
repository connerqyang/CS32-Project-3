#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

    // Actor: general class for all actors in the game, including Socrates
class Actor : public GraphObject
{
  public:
        // Constructor and Destructor
    Actor(int imageId, StudentWorld* world, double x, double y, Direction startDirection, int depth);
    virtual ~Actor() {}
    
        // Non-virtual functions
    bool isAlive() const;   // Returns true if m_isAlive is true, otherwise returns false
    void kill();            // Sets m_isAlive to false, effectively killing Actor
    StudentWorld* getWorldPtr() const;  // Returns a pointer to the StudentWorld that Actor is in

        // Pure-virtual functions
    virtual void doSomething() = 0;     // Pure virtual function for the actions of each Actor in a tick

  private:
    bool m_isAlive;         // Bool, is true if Actor is 'alive', otherwise returns false
    StudentWorld* m_world;  // Pointer to the world that Actor is in
};

    // AliveActor is a subclass of Actors that have hit points
class AliveActor : public Actor
{
  public:
        // Constructor and Destructor
    AliveActor(int imageId, StudentWorld* world, double x, double y, Direction startDirection, int depth, int hitPoints);
    virtual ~AliveActor() {}
    
        // Accessor and Mutator for m_hitPoints
    int getHitPoints() const;       // Returns the health/# of hit points of the AliveActor
    void addToHitPoints(int change);    // Adds parameter change to m_hitPoints (takes in negatives as well)
    
  private:
    int m_hitPoints;    // Health of the AliveActor
};

    // Socrates, the main character of the game
class Socrates : public AliveActor
{
  public:
        // Constructor and Destructor
    Socrates(StudentWorld* world);
    virtual ~Socrates() {}
    
        // Re-defined function
    virtual void doSomething();
    
  private:
    int getPositionalAngle() const;             // Returns the angle from the center's perspective
    void changePositionalAngle(int degrees);    // Modifies m_positionalAngle by parameter degrees
    void move();                        // moves Socrates to new location upon User's indication to move
    
    int m_positionalAngle;                      // Angle from center's perspective
    int m_numSprayCharges;                      // Number of Spray charges Socrates has left
    int m_numFlamethrowerCharges;               // Number of Flamethrower charges Socrates has left
};

class Dirt : public Actor
{
  public:
        // Constructor and Destructor
    Dirt(StudentWorld* world, double x, double y);
    virtual ~Dirt() {}
    
        // Re-defined function
    virtual void doSomething();         // "C'mon - it's dirt. What could it do?"
};

#endif // ACTOR_H_
