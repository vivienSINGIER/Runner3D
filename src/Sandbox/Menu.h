#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include <Containers/Vector.hpp>

#include "Button.h"
#include "Core/Scene.h"

class Menu : public Scene
{
public:
    Menu() = default;
    ~Menu() = default;
    void Init();
    void Uninit() { Scene::Uninit(); };
    void Update(float32 deltaTime);

private:
    Button* m_selectedBtn = nullptr;
    int8 m_indexBtn = 0;
    gce::Vector<Button*> m_vectButtons;
};

#endif