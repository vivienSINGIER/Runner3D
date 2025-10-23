#ifndef RUNNER3D_H_DEFINED
#define RUNNER3D_H_DEFINED

#include "Core/Scene.h"
#include "Character.h"
#include "Controller.h"

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
    Character* m_player = nullptr;
    Controller* m_playerController = nullptr;
    
    Player* player = nullptr;
    gce::Vector<Block*> m_vectBlocks;

    Block* m_lastBlockInCol =  nullptr;

    std::vector<Tile*> m_vectTiles;
    
    int8 m_currentTile = 0;

    void HandleTileSpawn();
    template <class BlockClass>
    void SpawnBlock(uint8 col);
    
    void InitTiles();
};

#endif