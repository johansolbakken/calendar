#include "application.h"

#include <knekt.h>

namespace calender
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        Knekt::ServerSpecification serverSpec;
        serverSpec.port = 8080;

        Knekt::Server server(serverSpec);
        server.get("/", [](Knekt::Request req) { 
            return Knekt::Response{Knekt::StatusCode::Ok, "Hello, World"}; 
        });

        while (true)
        {
            server.update();
        }
    }
}