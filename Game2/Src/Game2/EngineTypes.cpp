#include "pch.h"
#include "EngineTypes.h"

std::string c_stateToString(c_state state)
{
    switch (state)
    {
    case c_state::Static:   return "Static";
    case c_state::Walking:  return "Walking";
    case c_state::Idle:     return "Idle";
    case c_state::Attack:   return "Attack";
    default:                return "Unknown";
    }
}
