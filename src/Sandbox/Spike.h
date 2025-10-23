#ifndef SPIKE_H_DEFINED
#define SPIKE_H_DEFINED

#include "Block.h"

class Spike : public Block 
{
public:
    Spike() = default;
    ~Spike() = default;
    void Init(float32 speed) override;
};

#endif