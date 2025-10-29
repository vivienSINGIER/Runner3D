#ifndef SNWOMAN_H_DEFINED
#define SNWOMAN_H_DEFINED

#include "Block.h"

class Snowman : public Block 
{
public:
    Snowman() = default;
    ~Snowman() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
};

#endif