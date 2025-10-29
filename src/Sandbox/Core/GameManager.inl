#ifndef GAME_MANAGER_INL_DEFINED
#define GAME_MANAGER_INL_DEFINED
#include "Scene.h"

template <class SceneClass>
SceneClass* GameManager::AddScene()
{
    SceneClass* newScene = new SceneClass;
    Scene* casted = dynamic_cast<Scene*>(newScene);

    if (casted == nullptr) return nullptr;

    Get()->m_scenes.push_back(casted);
    
    return newScene;
}

template <class SceneClass>
bool GameManager::SetCurrentScene()
{
    for (Scene* scene : Get()->m_scenes)
    {
        SceneClass* casted = dynamic_cast<SceneClass*>(scene);
        if (casted == nullptr) continue;
        if (Get()->m_pCurrentScene != nullptr ) {Get()->m_pCurrentScene->Uninit();}
        Get()->m_pCurrentScene = scene;
        Get()->m_pCurrentScene->Init();
        return true;
    }
    return false;
}

#endif
