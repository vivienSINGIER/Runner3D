#ifndef GAME_MANAGER_H_DEFINED
#define GAME_MANAGER_H_DEFINED

#include <string_view>
#include <vector>
#include "Chrono.h"
#include "PhysicsSystem.h"

class Scene;


class GameManager
{
public:
    Chrono chrono;
    Camera* camera;

    void Init(std::wstring_view title, uint32 width, uint32 height);
    void GameLoop();

    template <class SceneClass> static SceneClass* AddScene();
    template <class SceneClass> static bool SetCurrentScene();
    Scene* GetCurrentScene() const { return m_pCurrentScene; }
    
    static GameManager* Get();
    float32 Deltatime();
    Window* GetWindow();
    
private:
    static GameManager* s_pInstance;
    Window* m_pWindow;
    PhysicsSystem m_physicsSystem;

    float32 m_deltatime = 0.0f;

    std::vector<Scene*> m_scenes;
    Scene* m_pCurrentScene = nullptr;
    
    GameManager();
    ~GameManager();
};

#include "GameManager.inl"

#endif

