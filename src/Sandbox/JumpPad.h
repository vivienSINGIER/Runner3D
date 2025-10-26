#ifndef JUMPPAD_H_DEFINED
#define JUMPPAD_H_DEFINED

#include "Block.h"

class JumpPad : public Block 
{
public:
    JumpPad() = default;
    ~JumpPad() = default;
    void Init(float32 speed) override;
};

#endif