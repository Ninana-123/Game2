#pragma once

#include "Application.h" 

#ifdef HZ_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
    Engine::Log::Init();
    CORE_WARN("Initialised Log");
    int a = 5;
    CORE_INFO("Hello Var={0}",a);


    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
    return 0; 
}

#endif
