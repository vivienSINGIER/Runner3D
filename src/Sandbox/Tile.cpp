#include "pch.h"
#ifndef TILE_CPP_DEFINED
#define TILE_CPP_DEFINED

#include "Tile.h"
#include <fstream>
#include <nlohmann.hpp>

void Tile::Init(int8 tile, std::wstring path)
{
    std::ifstream m_file = std::ifstream(path);
    nlohmann::json data;
    if (m_file.is_open()) data = nlohmann::json::parse(m_file);
    else return;

    if (data["Tiles"][tile]["full"]) {m_isPlain = true; return;}
    
    for (int i = 0; i < data["Tiles"][tile]["nbrBlock"]; i++)
    {
        gce::Vector3f32 pos = gce::Vector3f32(data["Tiles"][tile]["blocks"][i]["placement"][0],
            data["Tiles"][tile]["blocks"][i]["placement"][1],
            data["Tiles"][tile]["blocks"][i]["placement"][2]);
        AddObject(pos, ObjectType::Floor);
    }
}

void Tile::AddObject(gce::Vector3f32 pos, ObjectType type)
{
    if (type == ObjectType::Floor)      m_floorPos.push_back(pos);
    if (type == ObjectType::JumpPad)    m_jumpPadPos.push_back(pos);
    if (type == ObjectType::Spike)      m_spikePos.push_back(pos);
    if (type == ObjectType::Teleport)   m_teleportPos.push_back(pos);
}

#endif
