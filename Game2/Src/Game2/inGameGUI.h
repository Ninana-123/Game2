#pragma once

#ifndef INGAMEGUISYSTEM_H
#define INGAMEGUISYSTEM_H

#include "System.h"
#include "Entity.h"

namespace Engine
{
    class inGameGUISystem : public System 
    {
    public:
        void Update();


    private:
        int xPos = 0;
        int yPos = 0;
    };
}


#endif