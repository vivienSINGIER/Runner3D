#ifndef CHENE_H_DEFINED
#define CHENE_H_DEFINED

#include "Block.h"

class Chene : public Block 
{
public:
    Chene() = default;
    ~Chene() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
};

#endif