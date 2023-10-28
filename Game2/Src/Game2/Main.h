/******************************************************************************/
/*!
\file		Main.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Main entry point for the application.
            This file contains the main function that serves as the entry point
            for the application.
            It creates an instance of the application, initializes it, and 
            starts the application loop.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "Application.h" 
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "AssetManager.h"

int main(int argc, char** argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
    auto app = Engine::CreateApplication();
    app->Initialize();
    app->Run();
    
    return 0;
}