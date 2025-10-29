#ifndef SAND_H_DEFINED
#define SAND_H_DEFINED

#include "Block.h"

class Sand : public Block 
{
public:
    Sand() = default;
    ~Sand() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
};
#endif