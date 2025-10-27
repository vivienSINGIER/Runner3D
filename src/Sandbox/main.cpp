#include "pch.h"


#include "Runner3D.h"
#include "Test/TestScene.h"
#include "Core/GameManager.h"

#include "nlohmann.hpp"
#include <fstream>

#include "Menu.h"

int main()
{
    GameManager::Get()->Init(L"3D Runner", 1280, 720);
    GameManager::Get()->AddScene<Runner3D>();
    GameManager::Get()->AddScene<Menu>();
    GameManager::Get()->SetCurrentScene<Menu>();
    GameManager::Get()->GameLoop();
    return 0;
}
