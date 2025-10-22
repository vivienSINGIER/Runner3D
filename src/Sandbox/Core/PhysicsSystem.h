#ifndef PHYSICSSYSTEM_H_DEFINED
#define PHYSICSSYSTEM_H_DEFINED

class PhysicsSystem 
{
public:
    PhysicsSystem() = default;
    ~PhysicsSystem() = default;
    void PhysicsUpdate(float deltaTime);
    void CollisionCheck();
};

#endif
