#ifndef GRASS_H_DEFINED
#define GRASS_H_DEFINED

#include "Block.h"

class Grass : public Block 
{
public:
    Grass() = default;
    ~Grass() = default;
    void Init(gce::Vector3f32 const& pos, float32 speed) override;
};

#endif