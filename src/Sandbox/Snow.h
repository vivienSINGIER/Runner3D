#ifndef SNOW_H_DEFINED
#define SNOW_H_DEFINED

#include "Block.h"

class Snow : public Block 
{
public:
    Snow() = default;
    ~Snow() = default;
    void Init(float32 speed) override;
    void Start(uint8 col, float32 yPos) override;
};
#endif