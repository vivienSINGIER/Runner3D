#ifndef BUSH_H_DEFINED
#define BUSH_H_DEFINED

#include "Block.h"
class Bush : public Block
{
public:
    Bush() = default;
    ~Bush() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
    void Update(float32 deltaTime) override { Block::Update(deltaTime); };
};

#endif