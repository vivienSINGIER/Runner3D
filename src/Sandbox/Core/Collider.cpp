#include "pch.h"
#ifndef COLLIDER_CPP_DEFINED
#define COLLIDER_CPP_DEFINED

#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool Collider::IsAlreadyColliding(Collider* pOther)
{
    for (Collider* pCollider : m_collidingEntities)
    {
        if (pCollider == pOther) return true;
    }
    return false;
}

void Collider::Repulse(Collider* pOther)
{
    BoxCollider* boxCast = dynamic_cast<BoxCollider*>(pOther);
    if ((boxCast == nullptr) == false) RepulseBox(boxCast);

    SphereCollider* sphereCast = dynamic_cast<SphereCollider*>(pOther);
    if ((sphereCast == nullptr) == false) RepulseSphere(sphereCast);
}

void Collider::OnCollisionEnter(Collider* pOther)
{
    m_collidingEntities.push_back(pOther);   
}

void Collider::OnCollisionStay(Collider* pOther)
{
    if (m_rigidBody == true) Repulse(pOther);
}

void Collider::OnCollisionExit(Collider* pOther)
{
    for (int i = 0; i < m_collidingEntities.size(); i++)
    {
        m_collidingEntities.erase(m_collidingEntities.begin() + i);
    }
}

#endif


