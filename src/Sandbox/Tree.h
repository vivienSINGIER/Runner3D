#ifndef TREE_H_DEFINED
#define TREE_H_DEFINED

#include "Block.h"

class Tree : public Block 
{
public:
    Tree() = default;
    ~Tree() = default;
    void Init() override;
    void Start(uint8 col, float32 yPos) override;
};

#endif