#include "pch.h"
#ifndef SCENE_CPP_DEFINED
#define SCENE_CPP_DEFINED

#include "Scene.h"
#include "GC-simple-render/Window.h"
#include "GameObject.h"
#include "GC-simple-render/Text.h"
#include "GC-simple-render/InputsMethods.h"

Scene::~Scene()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        delete pGameObject;
    }
    for (Text* pText : m_uiElements)
    {
        delete pText;
    }

    m_gameObjects.clear();
    m_uiElements.clear();
}

void Scene::Update(float32 deltatime)
{
    if (GetKeyDown(Keyboard::Key::ESC)) m_isPaused = !m_isPaused;
    
    if (m_isPaused) return;
    
    for (GameObject* object : m_gameObjects)
    {
        if (object->IsActive()) object->Update(deltatime);
    }

    for (int i = 0; i < m_gameObjects.size(); i++ )
    {
        if (m_gameObjects[i]->toDestroy == true)
        {
            GameObject* temp = m_gameObjects[i];
            m_gameObjects.erase(m_gameObjects.begin() + i);
            delete temp;
        }
    }
}

void Scene::Draw(Window* pWindow)
{
    for (GameObject* object : m_gameObjects)
    {
        if (object->IsActive()) object->Render(pWindow);
    }
    for (Text* text : m_uiElements)
    {
        if (text == nullptr) continue;
        pWindow->DrawText(*text);
    }
}

Text* Scene::CreateText(std::wstring const& text)
{
    Text* pText = new Text(text);
    m_uiElements.push_back(pText);
    return pText;
}

#endif
