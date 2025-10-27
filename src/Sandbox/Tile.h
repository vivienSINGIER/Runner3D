#ifndef TILE_H_DEFINED
#define TILE_H_DEFINED
#include <format>
#include <vector>
#include <Maths/Vector3.h>

class Tile 
{
public:
    enum class ObjectType 
    {
        Floor, Object, JumpPad, Teleport
    };

    int8 m_currentRow = 0;
    
    bool m_isPlain = false;
    
    bool m_useTeleports = false;
    bool m_useJumpPads = false;

    std::vector<gce::Vector3f32> m_floorPos;
    std::vector<gce::Vector3f32> m_objectPos;
    
    std::vector<gce::Vector3f32> m_teleportPos;
    
    std::vector<gce::Vector3f32> m_jumpPadPos;

    Tile() = default;
    ~Tile() = default;

    void Init(int8 tile, std::wstring path);
    void AddObject(gce::Vector3f32 pos, ObjectType type);

};

#endif
