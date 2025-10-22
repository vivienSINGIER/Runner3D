#ifndef TESTPLAYER_H_DEFINED
#define TESTPLAYER_H_DEFINED
#include "Core/BoxCollider.h"
#include "Core/GameObject.h"
#include "Core/PhysicsComponent.h"

class TestPlayer : public GameObject, public BoxCollider, public PhysicsComponent
{
public:
    TestPlayer();
    ~TestPlayer() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime) override;
    
};

#endif
