#include "pch.h"
#ifndef PHYSICS_SYSTEM_CPP_DEFINED
#define PHYSICS_SYSTEM_CPP_DEFINED

#include "PhysicsSystem.h"

#include <vector>

#include "GameManager.h"
#include "Collider.h"

void PhysicsSystem::PhysicsUpdate()
{
    std::vector<Collider*> colliders = GameManager::Get()->GetCurrentScene()->GetAllComponents<Collider>();

    for (Collider* pCollider : colliders)
    {
        if (pCollider->m_isActiveCollider == false) continue;
        
        for (Collider* pOther : colliders)
        {
            if (pCollider == pOther) continue;
            
            if (pCollider->IsColliding(pOther))
            {
                if (pCollider->IsAlreadyColliding(pOther) == false)
                    pCollider->OnCollisionEnter(pOther);
                if (pCollider->IsAlreadyColliding(pOther) == true)
                    pCollider->OnCollisionStay(pOther);
            }
            else
            {
                if (pCollider->IsAlreadyColliding(pOther) == true)  pCollider->OnCollisionExit(pOther);
            }
        }
    }
}

#endif
