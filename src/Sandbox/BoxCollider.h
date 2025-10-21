#ifndef BOXCOLLIDER_H_DEFINED                       
#define BOXCOLLIDER_H_DEFINED

#include "Collider.h"

class SphereCollider;

class BoxCollider : public Collider
{
private:
    friend class SphereCollider;
    
protected:
    gce::Vector3f32 centre;
    gce::Vector3f32 size;

public:
    BoxCollider(gce::Vector3f32 centre, gce::Vector3f32 size);
    
    bool IsColliding(Collider* pOther) override;
    bool BoxToBox(BoxCollider* pOther);
    bool BoxToSphere(SphereCollider* pOther);

    void RepulseBox(BoxCollider* pOther) override;
    void RepulseSphere(SphereCollider* pOther) override;

};

#endif
