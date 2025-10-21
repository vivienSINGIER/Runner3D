#ifndef GAMEOBJECT_H_DEFINED
#define GAMEOBJECT_H_DEFINED

class Scene;

class GameObject
{
    
public:
    Transform m_transform;
    
    GameObject();
    virtual ~GameObject();

    virtual void Update(float32 deltatime);
    void Render(Window* window);
    void ToDestroy();
    
    void SetName(std::string newName);
    std::string GetName() { return m_name; }

protected:
    Geometry* m_mesh = nullptr;
    Scene* m_pScene = nullptr;

    bool toDestroy = false;
    std::string m_name;

private:
    friend class Scene;
    
};

#endif

