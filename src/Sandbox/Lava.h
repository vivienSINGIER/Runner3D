#ifndef LAVA_H_DEFINED
#define LAVA_H_DEFINED

#include "Block.h"

class Lava : public Block 
{
public:
    Lava() = default;
    ~Lava() = default;
    void Init(float32 speed) override;
    void Start(uint8 col, float32 yPos) override;
};

#endif