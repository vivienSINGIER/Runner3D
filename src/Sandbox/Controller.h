#ifndef CONTROLLER_H_DEFINED
#define CONTROLLER_H_DEFINED

#include "Character.h"

class Controller
{
public:
    void Init(Character* character) { m_character = character; }
    void HandleInput();
private:
    Character* m_character = nullptr;
};

#endif