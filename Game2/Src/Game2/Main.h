#pragma once

#include "Application.h" 

int main(int argc, char** argv)
{
    logger.Log(Engine::LogLevel::Debug, "Logger Initialized.");

    auto app = Engine::CreateApplication();
    app->Run();

    delete app;

    return 0;
}