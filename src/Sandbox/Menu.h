#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include "Core/Scene.h"

class Menu : public Scene
{
public:
    Menu() = default;
    ~Menu() = default;
    void Init();
    void Uninit();
    void Update(float32 deltaTime);
};

#endif