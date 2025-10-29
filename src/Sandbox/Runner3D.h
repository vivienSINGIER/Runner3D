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
class GameOver;

class Runner3D: public Scene
{
public:
    Runner3D() = default;
    ~Runner3D() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime);
    void AddScore(int32 score);
    void RotateCamera(int8 dir = 0);
    
private:
    enum BIOME
    {
        SNOW,
        DESERT,
        PLAINS
    };
    Character* m_player = nullptr;
    Controller* m_playerController = nullptr;

    int32 m_score = 0;
    
    std::ifstream m_file;
    nlohmann::json data;
    
    Player* player = nullptr;
    gce::Vector<Block*> m_vectBlocks;
    gce::Vector<Block*> m_vectObject;

    Block* m_lastBlockInCol =  nullptr;
    gce::Vector<Tile*> m_vectTiles;
    int8 m_currentTile = 0;
    bool m_hasStarted = false;
    Block* m_firstBlock = nullptr;

    Text* m_scoreText = nullptr;

    bool m_isReversing = false;
    bool m_isReversed = false;
    int8 m_tileCount = 0;

    Light* m_light = nullptr;

    BIOME m_biome = BIOME::PLAINS;
    
    void HandleTileSpawn();
    template <class BlockClass>
    void SpawnBlock(uint8 col);
    void SpawnObj(uint8 col);
    Block* ObjBiomeDesert(Block* obj);
    Block* ObjBiomeSnow(Block* obj);
    Block* ObjBiomePlains(Block* obj);
    void InitTiles();
    void WriteScore();
};

#endif