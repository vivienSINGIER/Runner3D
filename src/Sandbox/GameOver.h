#ifndef GAMEOVER_H_DEFINED
#define GAMEOVER_H_DEFINED
#include "Button.h"
#include "Core/Scene.h"

class GameOver : public Scene
{
public:
    GameOver() = default;
    ~GameOver() = default;
    void Init();
    void Uninit() override;
    void Update(float32 deltaTime) override;
private:
    int32 m_score;
    int32 m_bestScore;
};

#endif