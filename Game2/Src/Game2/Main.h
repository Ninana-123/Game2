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
#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H

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
 // Use the main entry point for Debug mode
#if defined(DEBUG) || defined(_DEBUG)

int main(int argc, char** argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_crtBreakAlloc = 13381;

    errorHandler.Initialize();
    auto app = Engine::CreateApplication();
    app->Initialize();
    app->Run();

    return 0;
}

#else

// Use WinMain entry point for Release mode
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    errorHandler.Initialize();
    auto app = Engine::CreateApplication();
    app->Initialize();
    app->Run();

    return 0;
}
#endif

#endif ENGINE_MAIN_H