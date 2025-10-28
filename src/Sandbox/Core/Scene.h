#ifndef SCENE_H_DEFINED
#define SCENE_H_DEFINED

class Text;

class GameObject;
class GameCamera;

class Scene
{
public:
    Scene() = default;
    virtual ~Scene();
    
    virtual void Update(float32 deltatime);
    void Draw(GameCamera* pGameCamera);

    virtual void Init() = 0;
    virtual void Uninit();

    template <class ObjectClass> ObjectClass* CreateObject();
    template <class ObjectClass> std::vector<GameObject*> GetAllObjects();
    template <class ComponentClass> std::vector<ComponentClass*> GetAllComponents();
    Text* CreateText(std::wstring const& text);

protected:
    bool m_isPaused = true;
    
private:
    std::vector<GameObject*> m_gameObjects;
    std::vector<Text*> m_uiElements;

    friend class GameManager;
};

#include "Scene.inl"

#endif

