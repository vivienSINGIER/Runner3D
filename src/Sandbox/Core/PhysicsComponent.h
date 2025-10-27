#ifndef PHYSICSCOMPONENT_H_DEFINED
#define PHYSICSCOMPONENT_H_DEFINED

class GameObject;

class PhysicsComponent
{
public:
    PhysicsComponent();
    ~PhysicsComponent();

    enum class Force
    {
        IMPULSE, FORCE
    };
    
    void AddForce(gce::Vector3f32 const& force, Force forceType);
    
protected:
    float32 m_speed = 0.0f;
    gce::Vector3f32 m_direction;
    gce::Vector3f32 m_velocity;

    bool m_useGravity = true;
    float32 m_gravity = -0.981f;
    float32 m_mass = 1.0f;

    int8 m_prioritizedAxis = -1;
    
    bool m_useMaxVelocityGlobal  = false;
    bool m_useMaxVelocityX       = false;
    bool m_useMaxVelocityY       = false;
    bool m_useMaxVelocityZ       = false;

    gce::Vector3f32 m_maxVelocities;
    float32 m_globalMaxVelocity = 10.0f;

    GameObject* m_pOwnerPhysics = nullptr;
    
private:
    std::vector<std::pair<gce::Vector3f32, Force>> m_appliedForces;
    gce::Vector3f32 m_previousVelocity;
    
    friend class PhysicsSystem;
    friend class BoxCollider;
    friend class SphereCollider;
    friend class Collider;
};

#endif
