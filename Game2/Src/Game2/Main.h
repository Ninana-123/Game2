#pragma once

#include "Application.h" 

int main(int argc, char** argv)
{
    auto app = Engine::CreateApplication();
    app->Run();

    delete app;

    return 0;
}