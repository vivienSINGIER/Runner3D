#ifndef GAMECAMERA_H_DEFINED
#define GAMECAMERA_H_DEFINED

class GameCamera
{
public:
    GameCamera();
    ~GameCamera();

    void Init(std::wstring_view title, uint32 width, uint32 height, CameraType type);
    void UnInit();
    
    void Draw(Geometry& geometry);
    void DrawText(Text& text);
    void Begin();
    void End();
    void Display();

    bool IsWindowOpen();
    
    //Transform Methods
    gce::Vector3f32 GetPosition();
    gce::Vector3f32 GetRotation();
    
    void SetPosition(gce::Vector3f32 const& position);
    void SetRotation(gce::Vector3f32 const& rotation);
    void SetFOV(float32 fov);
    void SetNearPlane(float32 nearPlane);
    void SetFarPlane(float32 farPlane);
    
private:
    Camera* m_pCamera = nullptr;
    Window* m_pWindow = nullptr;
};
#endif
