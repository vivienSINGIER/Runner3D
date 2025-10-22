#ifndef TESTSCENE_H_DEFINED
#define TESTSCENE_H_DEFINED

#include "Core/Scene.h"

class TestScene : public Scene
{
public:
    TestScene() = default;
    ~TestScene() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime);
};

#endif
