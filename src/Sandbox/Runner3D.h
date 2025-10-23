#ifndef RUNNER3D_H_DEFINED
#define RUNNER3D_H_DEFINED

#include "Core/Scene.h"
#include "Character.h"
#include "Controller.h"
#include "Block.h"

class Runner3D: public Scene
{
public:
    Runner3D() = default;
    ~Runner3D() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime);

private:
    gce::Vector<Block*> m_vectBlocks;

    Block* m_lastBlockInCol[3] = { nullptr, nullptr, nullptr };

    int32 const m_tiles[5][4][3] = {{{0, 1, 0},{ 1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
        {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 1, 1}},
        {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {1, 1, 1}},
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
        {{1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}}};

    int32 m_currentLine = 0.f;
    int32 m_currentTile = 0.f;
    
    float m_spawnZ = 20.f;
    float m_blockLength = 1.f;

    Character* m_player = nullptr;
    Controller* m_playerController = nullptr;
    void SpawnBlock(uint8 col);
};

#endif