#ifndef GAME_MANAGER_H_DEFINED
#define GAME_MANAGER_H_DEFINED

#include <string_view>
#include <vector>
#include "Chrono.h"
#include "PhysicsSystem.h"

class Scene;
class GameCamera;

class GameManager
{
public:
    Chrono chrono;
        
    void Init(std::wstring_view title, uint32 width, uint32 height);
    void GameLoop();
    
    template <class SceneClass> static SceneClass* AddScene();
    template <class SceneClass> static bool SetCurrentScene();
    Scene* GetCurrentScene() const { return m_pCurrentScene; }
    gce::Vector2i32 GetWindowSize() const { return m_windowSize; }
    
    static GameManager* Get();
    float32 Deltatime();
    Window* GetWindow();
    GameCamera* GetGameCamera() { return m_pGameCamera; }
    void SetGameCamera(GameCamera* pGameCamera) { m_pGameCamera = pGameCamera; }

    void CloseWindow() { m_isOpen = false; }
    
private:
    static GameManager* s_pInstance;
    PhysicsSystem m_physicsSystem;
    GameCamera* m_pGameCamera;

    gce::Vector2i32 m_windowSize;
    float32 m_deltatime = 0.0f;

    std::vector<Scene*> m_scenes;
    Scene* m_pCurrentScene = nullptr;

    bool m_isOpen = true;
    
    GameManager();
    ~GameManager();
};

#include "GameManager.inl"

#endif

