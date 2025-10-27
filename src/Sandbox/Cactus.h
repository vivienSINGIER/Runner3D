#ifndef CACTUS_H_DEFINED
#define CACTUS_H_DEFINED

#include "Block.h"
class Cactus : public Block
{
public:
    Cactus() = default;
    ~Cactus() = default;
    void Init(float32 speed) override;
    void Start(uint8 col, float32 yPos) override;
    void Update(float32 deltaTime) override { Block::Update(deltaTime); };
};

#endif