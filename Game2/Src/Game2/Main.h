#pragma once

#include "Application.h" 
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "logger.h"

Engine::Logger EntryPointLogger;
int main(int argc, char** argv)
{
    EntryPointLogger.Log(Engine::LogLevel::Debug, "Entry Point entered.");
    auto app = Engine::CreateApplication();
    app->Run();

    delete app;

    return 0;
}