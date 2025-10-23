#ifndef BLOCK_H_DEFINED
#define BLOCK_H_DEFINED
#include "Core/BoxCollider.h"
#include "Core/GameObject.h"

class Block : public GameObject, public BoxCollider
{
    
public:
    Block();
    ~Block() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime) override;

};

#endif