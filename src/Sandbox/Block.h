#ifndef BLOCK_H_DEFINED
#define BLOCK_H_DEFINED
#include "Core/BoxCollider.h"
#include "Core/Chrono.h"
#include "Core/GameObject.h"
#include "Core/PhysicsComponent.h"
#include "Core/PhysicsSystem.h"

#include "Core/Tween.hpp"

class Block : public GameObject, public BoxCollider, public PhysicsComponent
{
    
public:
    Block();
    ~Block() = default;
    virtual void Init(float32 speed);
    void Uninit();
    void Update(float32 deltaTime) override;
    void Start(uint8 col);
    bool IsSpawning() const { return m_isSpawning; }
    void SetIsSpawning(bool isSpawning) { m_isSpawning = isSpawning; };
private:
    float32 m_speed = 0.f;
    
    bool m_isTransited = false;
    bool m_isSpawning = false;
};


#endif