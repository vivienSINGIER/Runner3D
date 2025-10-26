#ifndef CHARACTER_H_DEFINED
#define CHARACTER_H_DEFINED
#include "Core/BoxCollider.h"
#include "Core/GameObject.h"
#include "Core/PhysicsComponent.h"

class Character : public GameObject, public BoxCollider, public PhysicsComponent
{
public:
    Character();
    ~Character() = default;
    
    void Init(gce::Vector3f32 pos);
    void Uninit();
    
    void Update(float32 deltaTime);
    void OnCollisionEnter(Collider* pOther) override;
    
    void Move(int8 dir);
    void Jump();
    void Start();
private:
    int8 col = 0.f;
    float32 m_speed = 100.f;
    bool m_isGrounded = false;
};

#endif