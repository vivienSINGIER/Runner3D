#ifndef RUNNER3D_H_DEFINED
#define RUNNER3D_H_DEFINED

#include "Block.h"
#include "Core/Scene.h"

class Player;
class Tile;

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

    Block* m_lastBlockInCol =  nullptr;

    int8 const m_tiles[5][4][3] = {{{0, 1, 0},{ 1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
        {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 1, 1}},
        {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {1, 1, 1}},
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
        {{1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}}};

    std::vector<Tile*> m_vectTiles;

    int8 m_currentLine = 0;
    int8 m_currentTile = 0;
    
    float m_spawnZ = 20.f;
    float m_blockLength = 1.f;

    void HandleTileSpawn();
    template <class BlockClass>
    void SpawnBlock(uint8 col);
    
    void InitTiles();
};

#endif