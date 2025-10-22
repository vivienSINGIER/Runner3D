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
    virtual void Init(gce::Vector3f32 const& pos, float32 speed);
    void Uninit();
    void Update(float32 deltaTime) override;
    bool Start();
    bool IsSpawning() const { return m_isSpawning; }
    void SetIsSpawning(bool isSpawning) { m_isSpawning = isSpawning; };
private:
    Chrono* m_endAnim = nullptr;
    Chrono* m_startAnim = nullptr;

    gce::Vector3f32 m_firstPos;
    float32 m_col = 0.f;

    float32 m_speed = 0.f;
    
    bool m_isTransited = false;
    bool m_isSpawning = false;
};


#endif