#ifndef RUNNER3D_H_DEFINED
#define RUNNER3D_H_DEFINED

#include "Core/Scene.h"
#include "Character.h"
#include "Controller.h"
#include <fstream>

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

    std::ifstream m_file;
};

#endif