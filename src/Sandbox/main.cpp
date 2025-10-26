#include "pch.h"


#include "Runner3D.h"
#include "Test/TestScene.h"
#include "Core/GameManager.h"

#include "nlohmann.hpp"
#include <fstream>

int main()
{
    GameManager::Get()->Init(L"3D Runner", 1280, 720, CameraType::PERSPECTIVE);
    GameManager::Get()->AddScene<Runner3D>();
    GameManager::Get()->SetCurrentScene<Runner3D>();
    GameManager::Get()->GameLoop();
    return 0;
}