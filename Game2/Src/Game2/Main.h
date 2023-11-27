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
#include "ErrorHandler.h"
Engine::ErrorHandler errorHandler;

/*!
 * \brief Main entry point for the application.
 * \param argc Number of command-line arguments.
 * \param argv Array of command-line arguments.
 * \return int The exit code.
 *
 * The main function serves as the entry point for the application. It creates
 * an instance of the application, initializes it, and starts the application loop.
 */
int main(int argc, char** argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    errorHandler.Initialize();
    auto app = Engine::CreateApplication();
    app->Initialize();
    app->Run();
    
    return 0;
}