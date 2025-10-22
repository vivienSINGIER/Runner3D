#ifndef SPIKE_H_DEFINED
#define SPIKE_H_DEFINED

#include "Block.h"

class Spike : public Block 
{
public:
    Spike() = default;
    ~Spike() = default;
    void Init(gce::Vector3f32 const& pos) override;
};

#endif