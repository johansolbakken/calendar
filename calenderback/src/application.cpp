#include "application.h"

#include <knekt.h>
#include <iostream>

#include "db.h"

namespace calender
{
    Application::Application()
    {
        Database::init();
    }

    Application::~Application()
    {
        Database::shutdown();
    }

    void Application::run()
    {
        Knekt::ServerSpecification serverSpec;
        serverSpec.port = 8080;

        Knekt::Server server(serverSpec);
        server.get("/", [](Knekt::Request req) { 
            return Knekt::Response{Knekt::StatusCode::Ok, "Hello, World"}; 
        });

        std::cout << "Server running on port " << serverSpec.port << std::endl;

        while (true)
        {
            server.update();
        }
    }
}