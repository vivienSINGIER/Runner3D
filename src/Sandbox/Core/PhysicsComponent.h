#ifndef PHYSICSCOMPONENT_H_DEFINED
#define PHYSICSCOMPONENT_H_DEFINED

class PhysicsComponent
{
public:
    PhysicsComponent();
    ~PhysicsComponent();

    enum class Force
    {
        IMPULSE, FORCE
    };
    
    void AddForce(gce::Vector3f32 const& force);
    
protected:
    float32 m_speed = 0.0f;
    gce::Vector3f32 m_direction;
    gce::Vector3f32 m_velocity;

    bool m_useGravity = true;
    float32 m_gravity = 981.0f;
    float32 m_mass = 1.0f;

    bool m_useMaxVelocityGlobal  = false;
    bool m_useMaxVelocityX       = false;
    bool m_useMaxVelocityY       = false;
    bool m_useMaxVelocityZ       = false;

    gce::Vector3f32 m_maxVelocities;
    float32 m_globalMaxVelocity = 0.0f;
    
private:
    std::vector<std::pair<gce::Vector3f32, Force>> m_appliedForces;
    gce::Vector3f32 m_previousVelocity;
    
    friend class PhysicsSystem;
};

#endif
