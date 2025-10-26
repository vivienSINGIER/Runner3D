#include "pch.h"
#ifndef CONTROLLER_CPP_DEFINED
#define CONTROLLER_CPP_DEFINED

#include "Controller.h"

void Controller::HandleInput()
{
    if (GetKeyDown(Keyboard::LEFT_ARROW) || GetKeyDown(Keyboard::Q)) {m_character->Move(-1);}
    if (GetKeyDown(Keyboard::RIGHT_ARROW) || GetKeyDown(Keyboard::D)) {m_character->Move(1);}
    if (GetKeyDown(Keyboard::A) || GetKeyDown(Keyboard::SPACE)) { m_character->Jump();}
    if (GetKeyDown(Keyboard::R)) { m_character->Respawn();}
}

#endif
