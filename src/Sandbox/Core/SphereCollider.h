#ifndef SPHERECOLLIDER_H_DEFINED
#define SPHERECOLLIDER_H_DEFINED

#include "Collider.h"
#include "Transform.h"

class BoxCollider;

class SphereCollider : public Collider
{
private:
    friend class BoxCollider;
protected:
    gce::Vector3f32 centre;
    float32 radius;

public:
    SphereCollider(gce::Vector3f32 centre, float32 radius);

    void RepulseBox(BoxCollider* pOther) override;
    void RepulseSphere(SphereCollider* pOther) override;
    
    bool IsColliding(Collider* pOther) override;
    bool SphereToSphere(SphereCollider* pOther);
    bool SphereToBox(BoxCollider* pOther);
};

#endif
