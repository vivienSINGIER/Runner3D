#ifndef RUNNER3D_H_DEFINED
#define RUNNER3D_H_DEFINED

#include <Containers/Vector.hpp>

#include "Core/Scene.h"
#include "Character.h"
#include "Controller.h"
#include <fstream>
#include <nlohmann.hpp>

class Block;

class Player;
class Tile;
class Block;

class Runner3D: public Scene
{
public:
    Runner3D() = default;
    ~Runner3D() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime);
    void AddScore(int32 score) { m_score += score; }

private:
    gce::CubeMap* skybox = nullptr;
    Character* m_player = nullptr;
    Controller* m_playerController = nullptr;

    int32 m_score = 0;
    
    std::ifstream m_file;
    nlohmann::json data;
    
    Player* player = nullptr;
    gce::Vector<Block*> m_vectBlocks;
    gce::Vector<Block*> m_vectObject;

    Block* m_lastBlockInCol =  nullptr;
    std::vector<Tile*> m_vectTiles;
    int8 m_currentTile = 0;

    bool m_hasStarted = false;
    Block* m_firstBlock = nullptr;

    Text* m_scoreText = nullptr;
    
    void HandleTileSpawn();
    template <class BlockClass>
    void SpawnBlock(uint8 col);
    void SpawnObj(uint8 col);

    void InitTiles();
};

#endif