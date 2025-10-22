#ifndef TESTBLOCK_H_DEFINED
#define TESTBLOCK_H_DEFINED

#include "Core/BoxCollider.h"
#include "Core/GameObject.h"

class TestBlock : public GameObject, public BoxCollider
{
public:
    TestBlock();
    ~TestBlock() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime) override;
};

#endif
