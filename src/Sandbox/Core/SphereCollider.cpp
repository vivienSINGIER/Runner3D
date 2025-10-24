#include "pch.h"
#ifndef SPHERECOLLIDER_CPP_DEFINED
#define SPHERECOLLIDER_CPP_DEFINED

#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Maths/MathsFunctions.hpp"

SphereCollider::SphereCollider(gce::Vector3f32 aCentre, float32 aRadius) : centre(aCentre), radius(aRadius)
{
    
}

void SphereCollider::RepulseBox(BoxCollider* o)
{
    float dt = GameManager::Get()->Deltatime();
    if (dt == 0.0f) dt = 0.001f;
    
    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity * GameManager::Get()->Deltatime();
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity * GameManager::Get()->Deltatime();
    
    float32 closestX = gce::Clamp(pos.x, oPos.x - o->size.x / 2.f, oPos.x + o->size.x / 2.f);
    float32 closestY = gce::Clamp(pos.y, oPos.y - o->size.y / 2.f, oPos.y + o->size.y / 2.f);
    float32 closestZ = gce::Clamp(pos.z, oPos.z - o->size.z / 2.f, oPos.z + o->size.z / 2.f);

    gce::Vector3f32 dir = pos - gce::Vector3f32(closestX, closestY, closestZ);
    float32 distance = gce::Sqrt(gce::Pow(closestX - pos.x, 2) + gce::Pow(closestY - pos.y, 2) + gce::Pow(closestZ - pos.z, 2));
    dir = (distance > 0) ? dir / distance : gce::Vector3f32(1.0f, 0.0f, 1.0f);

    gce::Vector3f32 push = dir * (radius - distance);

    PhysicsComponent* pC = dynamic_cast<PhysicsComponent*>(m_pOwner);
    PhysicsComponent* opC = dynamic_cast<PhysicsComponent*>(o->m_pOwner);
    
    if (o->m_rigidBody == true)
    {
        push /= 2.0f;
        if (opC != nullptr)
            opC->m_velocity -= push / dt;
        else
            o->m_pOwner->m_transform.Translate(-push);
    }
    if (pC != nullptr)
        pC->m_velocity += push / dt;
    else
        m_pOwner->m_transform.Translate(push);
}

void SphereCollider::RepulseSphere(SphereCollider* o)
{
    float dt = GameManager::Get()->Deltatime();
    if (dt == 0.0f) dt = 0.001f;
    
    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity * GameManager::Get()->Deltatime();
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity * GameManager::Get()->Deltatime();
    
    gce::Vector3f32 dir = pos - oPos;
    float32 distance = gce::Sqrt(gce::Pow(oPos.x - pos.x, 2) + gce::Pow(oPos.y - pos.y, 2) + gce::Pow(oPos.z - pos.z, 2));
    dir = (distance > 0) ? dir / distance : gce::Vector3f32(1.0f, 0.0f, 1.0f);

    gce::Vector3f32 push = dir * (radius - distance);

    PhysicsComponent* pC = dynamic_cast<PhysicsComponent*>(m_pOwner);
    PhysicsComponent* opC = dynamic_cast<PhysicsComponent*>(o->m_pOwner);
    
    if (o->m_rigidBody == true)
    {
        push /= 2.0f;
        if (opC != nullptr)
            opC->m_velocity -= push / dt;
        else
            o->m_pOwner->m_transform.Translate(-push);
    }
    if (pC != nullptr)
        pC->m_velocity += push / dt;
    else
        m_pOwner->m_transform.Translate(push);
}

bool SphereCollider::IsColliding(Collider* pOther)
{
    BoxCollider* oB = dynamic_cast<BoxCollider*>(pOther);
    if (oB != nullptr) return SphereToBox(oB);

    SphereCollider* oS = dynamic_cast<SphereCollider*>(pOther);
    if (oS != nullptr) return SphereToSphere(oS);
}

bool SphereCollider::SphereToSphere(SphereCollider* pOther)
{
    SphereCollider* o = pOther;
    if (o == nullptr) return false;

    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity;
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity;
    
    float32 distance = gce::Sqrt(gce::Pow(pos.x - oPos.x, 2) + gce::Pow(pos.y - oPos.y, 2) + gce::Pow(pos.z - oPos.z, 2));

    return (distance < radius + o->radius);
}

bool SphereCollider::SphereToBox(BoxCollider* pOther)
{
    return pOther->BoxToSphere(this);
}

#endif

