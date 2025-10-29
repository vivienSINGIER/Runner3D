#ifndef BUTTON_H_DEFINED
#define BUTTON_H_DEFINED

#include "Core/GameObject.h"

class Button : public GameObject
{
public:
    Button() = default;
    ~Button() = default;
    void Init(std::wstring const& text = L"");
    void Update(float32 deltaTime) override;
    void SetTextPos(int32 x, int32 y);
    void Select();
    void UnSelect();
private:
    Text* m_text = nullptr;
};

#endif 