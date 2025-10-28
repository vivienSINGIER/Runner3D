#ifndef SCENE_INL_DEFINED
#define SCENE_INL_DEFINED

#include "GameObject.h"

template <class ObjectClass>
std::vector<GameObject*> Scene::GetAllObjects()
{
    std::vector<GameObject*> vect;
    for (GameObject* object : m_gameObjects)
    {
        if (ObjectClass* casted = dynamic_cast<ObjectClass*>(object))
            vect.push_back(object);
    }
    return vect;
}

template <class ComponentClass>
std::vector<ComponentClass*> Scene::GetAllComponents()
{
    std::vector<ComponentClass*> vect;
    for (GameObject* object : m_gameObjects)
    {
        if (ComponentClass* casted = dynamic_cast<ComponentClass*>(object))
            vect.push_back(casted);
    }
    return vect;
}

template <class ObjectClass>
ObjectClass* Scene::CreateObject()
{
    ObjectClass* newObject = new ObjectClass();

    GameObject* casted = dynamic_cast<GameObject*>(newObject);
    if (casted == nullptr) return nullptr;

    casted->m_pScene = this;
    m_gameObjects.push_back(casted);
    return newObject;

}

#endif
