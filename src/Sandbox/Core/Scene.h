#ifndef SCENE_H_DEFINED
#define SCENE_H_DEFINED

class Text;

class GameObject;

class Scene
{
public:
    Scene() = default;
    virtual ~Scene();
    
    virtual void Update(float32 deltatime);
    void Draw(Window* pWindow);

    virtual void Init() = 0;

    template <class ObjectClass> ObjectClass* CreateObject();
    template <class ObjectClass> std::vector<GameObject*> GetAllObjects();
    template <class ComponentClass> std::vector<ComponentClass*> GetAllComponents();
    Text* CreateText(std::wstring const& text);
    
private:
    bool m_isPaused = true;
    
    std::vector<GameObject*> m_gameObjects;
    std::vector<Text*> m_uiElements;

    friend class GameManager;
};

#include "Scene.inl"

#endif

