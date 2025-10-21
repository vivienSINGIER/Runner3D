#ifndef BLOCK_H_DEFINED
#define BLOCK_H_DEFINED
#include "Core/BoxCollider.h"
#include "Core/Chrono.h"
#include "Core/GameObject.h"

#include "Core/Tween.hpp"

class Block : public GameObject, public BoxCollider
{
    
public:
    Block();
    ~Block() = default;
    void Init(gce::Vector3f32 pos);
    void Uninit();
    void Update(float32 deltaTime) override;
private:
    Chrono* m_transitAnim = nullptr;
    gce::Vector3f32 m_firstPos;
    bool m_isTransited;
};


#endif