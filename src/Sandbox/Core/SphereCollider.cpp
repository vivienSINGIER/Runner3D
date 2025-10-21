#include "pch.h"
#ifndef SPHERECOLLIDER_CPP_DEFINED
#define SPHERECOLLIDER_CPP_DEFINED

#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Maths/MathsFunctions.hpp"

SphereCollider::SphereCollider(gce::Vector3f32 aCentre, float32 aRadius) : centre(aCentre), radius(aRadius)
{
    
}

void SphereCollider::RepulseBox(BoxCollider* o)
{
    float32 closestX = gce::Clamp(centre.x, o->centre.x - o->size.x / 2.f, o->centre.x + o->size.x / 2.f);
    float32 closestY = gce::Clamp(centre.y, o->centre.y - o->size.y / 2.f, o->centre.y + o->size.y / 2.f);
    float32 closestZ = gce::Clamp(centre.z, o->centre.z - o->size.z / 2.f, o->centre.z + o->size.z / 2.f);

    gce::Vector3f32 dir = centre - gce::Vector3f32(closestX, closestY, closestZ);
    float32 distance = gce::Sqrt(gce::Pow(closestX - centre.x, 2) + gce::Pow(closestY - centre.y, 2) + gce::Pow(closestZ - centre.z, 2));
    dir = (distance > 0) ? dir / distance : gce::Vector3f32(1.0f, 0.0f, 1.0f);

    gce::Vector3f32 push = dir * (radius - distance);
    if (o->m_rigidBody == true)
    {
        push /= 2.0f;
        o->m_pOwner->m_transform.Translate(-push);
    }
    m_pOwner->m_transform.Translate(push);
}

void SphereCollider::RepulseSphere(SphereCollider* o)
{
    gce::Vector3f32 dir = centre - o->centre;
    float32 distance = gce::Sqrt(gce::Pow(o->centre.x - centre.x, 2) + gce::Pow(o->centre.y - centre.y, 2) + gce::Pow(o->centre.z - centre.z, 2));
    dir = (distance > 0) ? dir / distance : gce::Vector3f32(1.0f, 0.0f, 1.0f);

    gce::Vector3f32 push = dir * (radius - distance);
    if (o->m_rigidBody == true)
    {
        push /= 2.0f;
        o->m_pOwner->m_transform.Translate(push);
    }
    m_pOwner->m_transform.Translate(-push);
    
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
    float32 distance = gce::Sqrt(gce::Pow(centre.x - o->centre.x, 2) + gce::Pow(centre.y - o->centre.y, 2) + gce::Pow(centre.z - o->centre.z, 2));

    return (distance < radius + o->radius);
}

bool SphereCollider::SphereToBox(BoxCollider* pOther)
{
    return pOther->BoxToSphere(this);
}

#endif

