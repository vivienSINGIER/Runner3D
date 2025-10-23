#include "pch.h"
#ifndef TILE_CPP_DEFINED
#define TILE_CPP_DEFINED

#include "Tile.h"

void Tile::AddObject(gce::Vector3f32 pos, ObjectType type)
{
    if (type == ObjectType::Floor)      m_floorPos.push_back(pos);
    if (type == ObjectType::JumpPad)    m_jumpPadPos.push_back(pos);
    if (type == ObjectType::Spike)      m_spikePos.push_back(pos);
    if (type == ObjectType::Teleport)   m_teleportPos.push_back(pos);
}

#endif
