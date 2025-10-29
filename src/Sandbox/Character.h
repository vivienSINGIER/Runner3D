#ifndef CHARACTER_H_DEFINED
#define CHARACTER_H_DEFINED
#include "Block.h"
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
    void Crouch();
    void Start();
    void Respawn();

    void UpdateFromSpeed(float32 factor);
    void Reverse();
    void SetFirstReversedBlock(Block* block);

    bool GetIsAlive() { return m_isAlive; }
private:
    int8 col = 0.f;
    float32 m_rotationSpeed = 100.f;

    float32 m_JumpIntensity = 6.0f;
    
    bool m_isGrounded = false;
    bool m_isAlive = true;
    bool m_isReversed = false;
    bool m_hasStarted = false;

    Tween* leftTransitionTween = nullptr;
    Tween* rightTransitionTween = nullptr;
    
    Block* m_firstReversedBlock = nullptr;
};

#endif