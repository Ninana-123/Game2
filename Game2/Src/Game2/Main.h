#pragma once

#include "Application.h" 
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

int main(int argc, char** argv)
{
    auto app = Engine::CreateApplication();
    app->Run();

    delete app;

    return 0;
}