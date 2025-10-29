#ifndef THREE_H_DEFINED
#define THREE_H_DEFINED

#include "Block.h"

class Three : public Block 
{
public:
    Three() = default;
    ~Three() = default;
    void Init(float32 speed) override;
    void Start(uint8 col, float32 yPos) override;
};

#endif