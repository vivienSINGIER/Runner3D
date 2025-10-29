#ifndef SNOWBALL_H_DEFINED
#define SNOWBALL_H_DEFINED

#include "Block.h"
class Snowball : public Block
{
public:
    Snowball() = default;
    ~Snowball() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
    void Update(float32 deltaTime) override { Block::Update(deltaTime); };
};

#endif