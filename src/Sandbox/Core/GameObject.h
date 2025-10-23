#ifndef GAMEOBJECT_H_DEFINED
#define GAMEOBJECT_H_DEFINED

class Scene;
class GameCamera;

class GameObject
{
    
public:
    Transform m_transform;
    
    GameObject();
    virtual ~GameObject();

    virtual void Update(float32 deltatime);
    void Render(GameCamera* pGameCamera);
    void ToDestroy();
    
    bool IsActive() { return m_isActive;}
    void SetActive(bool active) { m_isActive = active;}
    void SetName(std::string newName);
    std::string GetName() { return m_name; }

protected:
    Geometry* m_mesh = nullptr;
    Scene* m_pScene = nullptr;

    bool toDestroy = false;
    bool m_isActive = true;
    std::string m_name;

private:
    friend class Scene;
    friend class PhysicsSystem;
    
};

#endif

