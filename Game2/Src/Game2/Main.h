#pragma once
#include "Application.h" 
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Logger.h"

int main(int argc, char** argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
    auto app = Engine::CreateApplication();
    app->Initialize();
    app->Run();
    
    return 0;
}