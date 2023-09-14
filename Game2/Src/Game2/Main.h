#pragma once

#include "Application.h" 
#include "logger.h"

int main(int argc, char** argv)
{
    Engine::Logger logger;
    // Example usage:
    logger.Log(Engine::LogLevel::Debug, "Logger Initialized.");

    auto app = Engine::CreateApplication();
    app->Run();
    delete app;

    return 0;
}