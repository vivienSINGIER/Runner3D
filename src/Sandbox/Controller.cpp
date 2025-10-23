#include "pch.h"
#ifndef CONTROLLER_CPP_DEFINED
#define CONTROLLER_CPP_DEFINED

#include "Controller.h"

void Controller::HandleInput()
{
    if (GetKeyDown(Keyboard::LEFT_ARROW)) {m_character->Move(-1);}
    if (GetKeyDown(Keyboard::RIGHT_ARROW)) {m_character->Move(1);}
    if (GetKeyDown(Keyboard::A)) { m_character->Jump();}
}

#endif
