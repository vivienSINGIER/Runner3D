#ifndef LAVA_H_DEFINED
#define LAVA_H_DEFINED

#include "Block.h"

class Lava : public Block 
{
public:
    Lava() = default;
    ~Lava() = default;
    void Init(gce::Vector3f32 const& pos, float32 speed) override;
};

#endif