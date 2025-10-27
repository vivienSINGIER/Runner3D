#ifndef GRASS_H_DEFINED
#define GRASS_H_DEFINED

#include "Block.h"

class Grass : public Block 
{
public:
    Grass() = default;
    ~Grass() = default;
    void Init(float32 speed) override;
    void Start(uint8 col, float32 yPos) override;
};
#endif