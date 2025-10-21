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
    GameCamera* m_pGameCamera;
        
    void Init(std::wstring_view title, uint32 width, uint32 height, CameraType type);
    void GameLoop();
    
    template <class SceneClass> static SceneClass* AddScene();
    template <class SceneClass> static bool SetCurrentScene();
    Scene* GetCurrentScene() const { return m_pCurrentScene; }
    
    static GameManager* Get();
    float32 Deltatime();
    Window* GetWindow();
    
private:
    static GameManager* s_pInstance;
    PhysicsSystem m_physicsSystem;

    float32 m_deltatime = 0.0f;

    std::vector<Scene*> m_scenes;
    Scene* m_pCurrentScene = nullptr;
    
    GameManager();
    ~GameManager();
};

#include "GameManager.inl"

#endif

