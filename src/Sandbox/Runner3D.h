#ifndef RUNNER3D_H_DEFINED
#define RUNNER3D_H_DEFINED

#include "Block.h"
#include "Core/Scene.h"

class Player;

class Runner3D: public Scene
{
public:
    Runner3D() = default;
    ~Runner3D() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime);

private:
    Player* player = nullptr;
};

#endif