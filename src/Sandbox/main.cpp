#include "pch.h"


#include "GameOver.h"
#include "Runner3D.h"
#include "Core/GameManager.h"
#include "nlohmann.hpp"

#include "Menu.h"

int main()
{
    GameManager::Get()->Init(L"3D Runner", 1920, 1080);
    GameManager::Get()->AddScene<Runner3D>();
    GameManager::Get()->AddScene<Menu>();
    GameManager::Get()->AddScene<GameOver>();
    GameManager::Get()->SetCurrentScene<Menu>();
    GameManager::Get()->GameLoop();
    return 0;
}
