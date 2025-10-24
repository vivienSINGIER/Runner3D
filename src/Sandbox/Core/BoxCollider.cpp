#include "pch.h"
#ifndef BOX_COLLIDER_CPP_DEFINED
#define BOX_COLLIDER_CPP_DEFINED

#include "BoxCollider.h"

#include "GameManager.h"
#include "GameObject.h"
#include "SphereCollider.h"
#include "Maths/MathsFunctions.hpp"
#include "PhysicsComponent.h"

BoxCollider::BoxCollider(gce::Vector3f32 centre, gce::Vector3f32 size) : centre(centre), size(size) {}


bool BoxCollider::IsColliding(Collider* pOther)
{
    BoxCollider* oB = dynamic_cast<BoxCollider*>(pOther);
    if (oB != nullptr) return BoxToBox(oB);

    SphereCollider* oS = dynamic_cast<SphereCollider*>(pOther);
    if (oS != nullptr) return BoxToSphere(oS);

    return false;
}

bool BoxCollider::BoxToBox(BoxCollider* pOther)
{
    BoxCollider* o = pOther;
    if (o == nullptr) return false;

    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity * GameManager::Get()->Deltatime();
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity * GameManager::Get()->Deltatime();
    
    float32 minRadius = gce::Sqrt(gce::Pow(size.x / 2.0f, 2) + gce::Pow(size.y / 2.0f, 2) + gce::Pow(size.z / 2.0f, 2));
    
    float32 oMinRadius = gce::Sqrt(gce::Pow(o->size.x / 2.0f, 2) + gce::Pow(o->size.y / 2.0f, 2) + gce::Pow(o->size.z / 2.0f, 2));

    float32 distance = gce::Sqrt(gce::Pow(pos.x - oPos.x, 2) + gce::Pow(pos.y - oPos.y, 2) + gce::Pow(pos.z - oPos.z, 2));

    if (distance > minRadius  + oMinRadius ) return false;

    gce::Vector3f32 half(size.x / 2.f, size.y / 2.f, size.z / 2.f);
    gce::Vector3f32 oHalf(o->size.x / 2.f, o->size.y / 2.f, o->size.z / 2.f);

    int intersectTotal = 0;
    intersectTotal += (gce::Abs(pos.x - oPos.x) <= half.x + oHalf.x) ? 1 : 0;
    intersectTotal += (gce::Abs(pos.y - oPos.y) <= half.y + oHalf.y) ? 1 : 0;
    intersectTotal += (gce::Abs(pos.z - oPos.z) <= half.z + oHalf.z) ? 1 : 0;

    return intersectTotal == 3;
}

bool BoxCollider::BoxToSphere(SphereCollider* pOther)
{
    SphereCollider* o = pOther;
    if (o == nullptr) return false;

    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity * GameManager::Get()->Deltatime();
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity * GameManager::Get()->Deltatime();
    
    float32 minRadius = gce::Sqrt(gce::Pow(size.x / 2.0f, 2) + gce::Pow(size.y / 2.0f, 2) + gce::Pow(size.z / 2.0f, 2));
    float32 distance = gce::Sqrt(gce::Pow(pos.x - oPos.x, 2) + gce::Pow(pos.y - oPos.y, 2) + gce::Pow(pos.z - oPos.z, 2));

    if (distance > minRadius + o->radius) return false;
    float32 closestX = gce::Clamp(oPos.x, pos.x - size.x / 2.f, pos.x + size.x / 2.f);
    float32 closestY = gce::Clamp(oPos.y, pos.y - size.y / 2.f, pos.y + size.y / 2.f);
    float32 closestZ = gce::Clamp(oPos.z, pos.z - size.z / 2.f, pos.z + size.z / 2.f);

    distance = gce::Sqrt(gce::Pow(closestX - oPos.x, 2) + gce::Pow(closestY - oPos.y, 2) + gce::Pow(closestZ - oPos.z, 2));
    
    return distance < o->radius;
}

void BoxCollider::RepulseBox(BoxCollider* o)
{
    if (o == nullptr) return;

    float dt = GameManager::Get()->Deltatime();
    if (dt == 0.0f) dt = 0.001f;
    
    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity * dt;
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity * dt;
    
    gce::Vector3f32 minA = gce::Vector3f32(pos.x - size.x / 2.f, pos.y - size.y / 2.f, pos.z - size.z / 2.f);
    gce::Vector3f32 maxA = gce::Vector3f32(pos.x + size.x / 2.f, pos.y + size.y / 2.f, pos.z + size.z / 2.f);

    gce::Vector3f32 minB = gce::Vector3f32(oPos.x - o->size.x / 2.f, oPos.y - o->size.y / 2.f, oPos.z - o->size.z / 2.f);
    gce::Vector3f32 maxB = gce::Vector3f32(oPos.x + o->size.x / 2.f, oPos.y + o->size.y / 2.f, oPos.z + o->size.z / 2.f);

    float32 overlapX = gce::Min(maxA.x, maxB.x) - gce::Max(minA.x, minB.x);
    float32 overlapY = gce::Min(maxA.y, maxB.y) - gce::Max(minA.y, minB.y);
    float32 overlapZ = gce::Min(maxA.z, maxB.z) - gce::Max(minA.z, minB.z);

    float minOverlap = abs(overlapX);
    int overlapIndex = 0;

    if (abs(overlapY) < minOverlap)
    {
        minOverlap = overlapY;
        overlapIndex = 1;
    }
    if (abs(overlapZ) < minOverlap)
    {
        minOverlap = overlapZ;
        overlapIndex = 2;
    }

    if (minOverlap < 0.0000001f) return;
    
    float push = 0.0f;

    PhysicsComponent* pC = dynamic_cast<PhysicsComponent*>(m_pOwner);
    PhysicsComponent* opC = dynamic_cast<PhysicsComponent*>(o->m_pOwner);
    
    switch (overlapIndex)
    {
    case 0:
        push = (pos.x < oPos.x) ? -overlapX : overlapX;
        if (o->m_rigidBody == true)
        {
            push /= 2.0f;
            if (opC != nullptr)
                opC->m_velocity.x += -push / dt;
            else
                o->m_pOwner->m_transform.Translate(gce::Vector3f32(-push, 0.0f, 0.0f));
        }
        if (pC != nullptr)
            pC->m_velocity.x += push / dt;
        else
            m_pOwner->m_transform.Translate(gce::Vector3f32(push, 0.0f, 0.0f));
        break;
    case 1:
        push = (pos.y < oPos.y) ? -overlapY : overlapY;
        if (o->m_rigidBody == true)
        {
            push /= 2.0f;
            if (opC != nullptr)
                opC->m_velocity.y += -push / dt;
            else
                o->m_pOwner->m_transform.Translate(gce::Vector3f32(0.0f, -push, 0.0f));
        }
        if (pC != nullptr)
            pC->m_velocity.y += push / dt;
        else
            m_pOwner->m_transform.Translate(gce::Vector3f32(0.0f, push, 0.0f));
        if (pC->m_velocity.y > 1.0f)
            int o = 0;
        break;
    case 2:
        push = (pos.z < oPos.z) ? -overlapZ : overlapZ;
        if (o->m_rigidBody == true)
        {
            push /= 2.0f;
            if (opC != nullptr)
                opC->m_velocity.z += -push / dt;
            else
                o->m_pOwner->m_transform.Translate(gce::Vector3f32(0.0f, 0.0f, -push));
        }
        if (pC != nullptr)
            pC->m_velocity.z += push / dt ;
        else
            m_pOwner->m_transform.Translate(gce::Vector3f32(0.0f, 0.0f, push));
        break;
    }
}

void BoxCollider::RepulseSphere(SphereCollider* o)
{
    if (o == nullptr) return;

    float dt = GameManager::Get()->Deltatime();
    if (dt == 0.0f) dt = 0.001f;
    
    gce::Vector3f32 pos = centre;
    gce::Vector3f32 oPos = o->centre;
    PhysicsComponent* casted = dynamic_cast<PhysicsComponent*>(GetOwner());
    PhysicsComponent* oCasted = dynamic_cast<PhysicsComponent*>(o->GetOwner());
    if (casted != nullptr)
        pos += casted->m_velocity * dt;
    if (oCasted != nullptr)
        oPos += oCasted->m_velocity * dt;
    
    float32 closestX = gce::Clamp(oPos.x, pos.x - size.x / 2.f, pos.x + size.x / 2.f);
    float32 closestY = gce::Clamp(oPos.y, pos.y - size.y / 2.f, pos.y + size.y / 2.f);
    float32 closestZ = gce::Clamp(oPos.z, pos.z - size.z / 2.f, pos.z + size.z / 2.f);

    gce::Vector3f32 dir = oPos - gce::Vector3f32(closestX, closestY, closestZ);
    float32 distance = gce::Sqrt(gce::Pow(closestX - oPos.x, 2) + gce::Pow(closestY - oPos.y, 2) + gce::Pow(closestZ - oPos.z, 2));
    dir = (distance > 0) ? dir / distance : gce::Vector3f32(1.0f, 0.0f, 1.0f);
    
    gce::Vector3f32 push = dir * (o->radius - distance);

    PhysicsComponent* pC = dynamic_cast<PhysicsComponent*>(m_pOwner);
    PhysicsComponent* opC = dynamic_cast<PhysicsComponent*>(o->m_pOwner);
    
    if (o->m_rigidBody == true)
    {
        push /= 2.0f;
        if (opC != nullptr)
            opC->m_velocity += push / dt;
        else
            o->m_pOwner->m_transform.Translate(push);
    }
    if (pC != nullptr)
        pC->m_velocity += push / dt;
    else
        m_pOwner->m_transform.Translate(-push);
}

#endif
