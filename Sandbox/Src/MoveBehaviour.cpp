
#include "Game2\Main.h"


class Sandbox : public Engine::Application
{
public:
    Sandbox()
    {
        // Constructor implementation
    }

    ~Sandbox()
    {
        // Destructor implementation
    }
};

Engine::Application* Engine::CreateApplication()
{
    return new Sandbox();
}
