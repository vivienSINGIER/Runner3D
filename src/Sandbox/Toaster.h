#ifndef TOASTER_H_DEFINED
#define TOASTER_H_DEFINED

#include "Block.h"
class Toaster : public Block
{
public:
    Toaster() = default;
    ~Toaster() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
    void Update(float32 deltaTime) override;
};

#endif