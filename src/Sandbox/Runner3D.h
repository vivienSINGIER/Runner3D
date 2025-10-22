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
    gce::Vector<Block*> m_vectBlocks;

    Block* m_lastBlockInCol[3] = { nullptr, nullptr, nullptr };

    float m_spawnZ = 20.f;
    float m_blockLength = 1.f;

    void SpawnBlock(uint8 col);
};

#endif