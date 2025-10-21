#ifndef TWEEN_HPP_DEFINED
#define TWEEN_HPP_DEFINED
#include <Containers/Vector.hpp>

#include "define.h"
#include "Geometries.h"

enum Function
{
    Position,
    Rotation,
    Scale
};

class Tween
{
public:
    inline void StartDuration(float32 duration, Function typeFunction, Geometry* pOwnerTransform, bool reverse);

private:
    Tween(gce::Vector3f32 const& start, gce::Vector3f32 const& end, float32(* const pFunction)(float32));
    void Update(float32 const deltaTime);
    gce::Vector3f32 start, end;
    float32(* function)(float32)  = nullptr;

    struct infoTween { float32 mDuration; float32 mElapsed = 0.f; Function mTypeFunction; Geometry* mOwnerTransform; bool mReverse; };
    infoTween* mTween;
    
    friend class TweenSystem;
};

class TweenSystem
{

public:
    inline static Tween* Create(gce::Vector3f32 const& pStart, gce::Vector3f32 const& pEnd, float32(* const pFunction)(float32) );
    inline static void Update(float32 deltaTime);

private:
    inline static float32 dt;
    inline static gce::Vector<Tween*> tweens;

    static float32 GetDeltaTime() { return dt; }; 
};

inline Tween::Tween(gce::Vector3f32 const&  pStart, gce::Vector3f32 const& pEnd, float32(* const pFunction)(float32))
{
    start = pStart;
    end = pEnd;
    function = pFunction;
}

inline void Tween::StartDuration(float32 duration, Function typeFunction, Geometry* pOwnerTransform, bool reverse)
{
    mTween = new infoTween();
    mTween->mDuration = duration;
    mTween->mTypeFunction = typeFunction;
    mTween->mOwnerTransform = pOwnerTransform;
    mTween->mReverse = reverse;
}

inline void Tween::Update(float32 const deltaTime)
{
    if (mTween == nullptr) return;
    
    float32 const dt = deltaTime;
    mTween->mElapsed += dt;
    float32 const progress = mTween->mReverse ? 1.0f - mTween->mElapsed / mTween->mDuration : mTween->mElapsed / mTween->mDuration;
    switch (mTween->mTypeFunction)
    {
    case Function::Position:
        mTween->mOwnerTransform->SetPosition(start + (end - start) * function(progress <= 1.0f ? progress : 1.0f));
        break;
    case Function::Rotation:
        mTween->mOwnerTransform->SetRotation(start + (end - start) * function(progress <= 1.0f ? progress : 1.0f));
        break;
    case Function::Scale:
        mTween->mOwnerTransform->SetScale(start + (end - start) * function(progress <= 1.0f ? progress : 1.0f));
        break;
    };
    if (mTween->mElapsed >= mTween->mDuration) mTween = nullptr;
}    

inline Tween* TweenSystem::Create(gce::Vector3f32 const& start, gce::Vector3f32 const& end, float32(* const pFunction)(float32))
{
    Tween* tween = new Tween(start,end,pFunction);
    tweens.PushBack(tween);
    return tween;
}

inline void TweenSystem::Update(float32 const deltaTime)
{
    dt = deltaTime;
    for (Tween* t : tweens) t->Update(deltaTime);
}

struct Interpolation 
{
public:
    static float32 easingIn_linear(float32 x) { return x; }
    static float32 easingOut_linear(float32 x) { return x; }
    static float32 easingInAndOut_linear(float32 x) { return x; }
    
    static float32 easingIn_Quad(float32 const x) { return x * x; }
    static float32 easingOut_Quad(float32 const x) { return 1.0f - (1.0f - x) * (1.0f - x); }
    static float32 easingInOut_Quad(float32 const x) { return x < 0.5f ? 2.0f * x * x : (4.0f - 2.0f * x) * x - 1.0f; }
    
    static float32 easingIn_cubic(float32 x) { return x * x * x; }
    static float32 easingOut_cubic(float32 x) { return x * x * x; }
    static float32 easingInAndOut_cubic(float32 x) { return x * x * x * x; }

    static float32 easingIn_quad(float32 x) { return x * x * x * x; }
    static float32 easingOut_quad(float32 x) { return x * x * x * x; }
    static float32 easingInAndOut_quad(float32 x) { return x * x * x * x; }
};

#endif