#include "pch.h"
#ifndef PHYSICSCOMPONENT_CPP_DEFINED
#define PHYSICSCOMPONENT_CPP_DEFINED

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent() :
    m_direction(), m_velocity(), m_maxVelocities(), m_previousVelocity()
{
    
}

PhysicsComponent::~PhysicsComponent()
{
    
}

void PhysicsComponent::AddForce(gce::Vector3f32 const& force, Force forceType)
{
    if (force.y > 0)
        int o = 0;
    m_appliedForces.push_back(std::make_pair(force, forceType));
}


#endif
